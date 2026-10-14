#!/usr/bin/env python3
"""Count the references to an address in the image (Phase 5 boundary evidence).

Reports, per requested address: how many `jal`/`j` sites target it, how many
`lui`+immediate sites materialise it, and whether the raw 32-bit word appears
anywhere (a function-pointer table entry in .data/.rodata).

Used to decide whether a splat `glabel` is a real function entry. All six
4-byte-aligned starts besides 0x00113074 that spimdisasm promoted have call
sites; 0x00113074 has none of any kind (see docs/naming-candidates.md,
"Boundary re-check").

    python3 tools/ref_check.py 0x00113074 0x00113078
"""
from __future__ import annotations

import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BASE = 0x00100000
IMM_OPS = {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
           0x20, 0x21, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
           0x2A, 0x2B, 0x2E}


def main() -> int:
    rom = (ROOT / "build" / "SCUS_974.72.rom").read_bytes()
    n = len(rom) // 4
    words = [struct.unpack_from("<I", rom, k * 4)[0] for k in range(n)]
    targets = [int(a, 0) for a in sys.argv[1:]]
    if not targets:
        print(__doc__, file=sys.stderr)
        return 2
    jumps: dict[int, list[int]] = {t: [] for t in targets}
    refs: dict[int, list[int]] = {t: [] for t in targets}
    literals: dict[int, list[int]] = {t: [] for t in targets}

    for i, w in enumerate(words):
        op = w >> 26
        va = BASE + i * 4
        if op in (2, 3):  # j / jal
            t = (va & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
            if t in jumps:
                jumps[t].append(va)
        elif op == 0x0F:  # lui; look for the paired immediate materialisation
            reg = (w >> 16) & 0x1F
            hi = (w & 0xFFFF) << 16
            for j in range(i + 1, min(i + 8, n)):
                w2 = words[j]
                op2 = w2 >> 26
                if op2 == 0x0F:
                    break
                if op2 not in IMM_OPS or ((w2 >> 21) & 0x1F) != reg:
                    continue
                lo = w2 & 0xFFFF
                if lo & 0x8000:
                    lo -= 0x10000
                v = hi + lo
                if v in refs:
                    refs[v].append(BASE + j * 4)
                break
        if w in literals:
            literals[w].append(va)

    rc = 0
    for t in targets:
        print("0x%08X: jal/j=%d  lui-relative=%d  literal-words=%d"
              % (t, len(jumps[t]), len(refs[t]), len(literals[t])))
        for label, sites in (("jal/j", jumps[t]), ("ref", refs[t]),
                            ("literal", literals[t])):
            if sites:
                print("    %-7s from %s"
                      % (label, " ".join("0x%08X" % s for s in sites[:8])))
        if not (jumps[t] or refs[t] or literals[t]):
            rc += 1
    print("%d/%d address(es) unreferenced" % (rc, len(targets)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
