#!/usr/bin/env python3
"""Show where two flat images differ, mapped to the splat function that covers
each differing address (uses config/SCUS_974.72.yaml subsegment starts).

    python3 tools/bin_diff.py build/SCUS_974.72.bin build/SCUS_974.72.rom
"""
from __future__ import annotations

import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ROM_BASE = 0x00100000
SEG_RE = re.compile(r"^\s*- \[0x([0-9A-Fa-f]+), \w+, cod/([0-9A-Fa-f]+)\]")


def splat_spans() -> list[tuple[int, str]]:
    """(vaddr, name) for every cod subsegment, sorted."""
    out: list[tuple[int, str]] = []
    for line in (ROOT / "config" / "SCUS_974.72.yaml").read_text(
            encoding="utf-8").splitlines():
        m = SEG_RE.match(line)
        if m:
            out.append((int(m.group(1), 16) + ROM_BASE, m.group(2)))
    out.sort()
    return out


def owner(vaddr: int, spans: list[tuple[int, str]]) -> str:
    lo, hi = 0, len(spans) - 1
    best = ""
    for a, n in spans:
        if a <= vaddr:
            best = n
        else:
            break
    return best


def main() -> int:
    a = Path(sys.argv[1] if len(sys.argv) > 1 else "build/SCUS_974.72.bin").read_bytes()
    b = Path(sys.argv[2] if len(sys.argv) > 2 else "build/SCUS_974.72.rom").read_bytes()
    spans = splat_spans()
    print(f"a={len(a)} bytes  b={len(b)} bytes")
    n = min(len(a), len(b))
    runs: list[tuple[int, int]] = []
    start = None
    for i in range(n):
        if a[i] != b[i]:
            if start is None:
                start = i
        else:
            if start is not None:
                runs.append((start, i))
                start = None
    if start is not None:
        runs.append((start, n))
    print(f"{len(runs)} differing run(s), {sum(e - s for s, e in runs)} bytes")
    for s, e in runs[:40]:
        va = s + ROM_BASE
        print(f"  {s:#08x}..{e:#08x} (vaddr {va:#08x}, {e - s} bytes) "
              f"func {owner(va, spans)}")
        for off in range(s, min(e, s + 32), 4):
            wa, = struct.unpack_from("<I", a, off)
            wb, = struct.unpack_from("<I", b, off)
            print(f"      +{off - s:#04x} mine {wa:08X}  orig {wb:08X}")
    return 0 if not runs else 1


if __name__ == "__main__":
    raise SystemExit(main())
