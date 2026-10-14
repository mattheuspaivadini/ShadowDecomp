#!/usr/bin/env python3
"""Audit addressing modes in the original image (Phase 3 evidence).

Answers two questions that pin the `-G` (small-data) flag and whether the
original linker relaxed out-of-range gp-relative references:

1. `%gp_rel` accesses whose resolved address falls *outside* the gp window
   [_gp-0x8000, _gp+0x7FFF]. The compiler only emits gp-relative code for
   small data, so an out-of-window target means the original linker rewrote
   (`relaxed`) it -- something Debian `mips-linux-gnu-ld` refuses to do.
2. Absolute `lui/%hi + %lo` accesses whose resolved address falls *inside*
   `.sdata`/`.sbss` (which by definition holds small data). Those can only
   happen if the translation unit was compiled with small data disabled
   (`-G0`), i.e. a per-file flag difference.

Usage: python3 tools/scan_sdata_access.py [--rom build/SCUS_974.72.rom]
"""
from __future__ import annotations

import argparse
import struct
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ROM_BASE = 0x00100000
GP = 0x00141D70
GP_LO, GP_HI = GP - 0x8000, GP + 0x7FFF

# section ranges from build/SCUS_974.72.map
SECTIONS = [
    ("text", 0x00100000, 0x00131BAC),
    ("data", 0x00131BAC, 0x00136100),
    ("rodata", 0x00136100, 0x00139D80),
    ("lit4", 0x00139D80, 0x00139E00),
    ("sdata", 0x00139E00, 0x0013A180),
    ("sbss", 0x0013A180, 0x0013A200),
    ("bss", 0x0013A200, 0x0016A328),
]

# loads/stores with a 16-bit signed immediate: (opcode, base_field_is_rs)
MEM = {
    0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu", 0x25: "lhu",
    0x22: "lwl", 0x26: "lwr", 0x27: "lwu", 0x1A: "ldl", 0x1B: "ldr",
    0x28: "sb", 0x29: "sh", 0x2B: "sw", 0x2A: "swl", 0x2E: "swr",
    0x2C: "sdl", 0x2D: "sdr",
    0x37: "ld", 0x3F: "sd",
    0x31: "lwc1", 0x35: "ldc1", 0x39: "swc1", 0x3D: "sdc1",
    0x32: "lwc2", 0x3A: "swc2", 0x36: "lqc2", 0x3E: "sqc2",
    0x1F: "sq", 0x30: "lq",  # EE: 0x1F/0x30 with imm
}
# instructions that write a GPR in the `rt` field (I-type / loads)
WRITES_RT = set(MEM) | {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                        0x18, 0x19} | {0x33, 0x3B}  # ll, sc


def sign16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def section_of(addr: int) -> str:
    for name, lo, hi in SECTIONS:
        if lo <= addr < hi:
            return name
    return "?"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", type=Path, default=ROOT / "build" / "SCUS_974.72.rom")
    args = ap.parse_args()
    d = args.rom.read_bytes()
    words = struct.unpack_from(f"<{len(d) // 4}I", d, 0)

    gp_targets: Counter = Counter()
    gp_out_of_window = Counter()
    abs_targets: Counter = Counter()
    abs_small_data = Counter()
    last_lui: dict[int, tuple[int, int]] = {}

    for i, w in enumerate(words):
        op = w >> 26
        rs = (w >> 21) & 0x1F
        rt = (w >> 16) & 0x1F
        rd = (w >> 11) & 0x1F
        imm = sign16(w & 0xFFFF)

        if op == 0x0F:  # lui
            last_lui[rt] = ((w & 0xFFFF) << 16, i)
        elif op in MEM:
            if rs == 28:  # gp-relative
                tgt = GP + imm
                gp_targets[section_of(tgt)] += 1
                if not (GP_LO <= tgt <= GP_HI):
                    gp_out_of_window[(section_of(tgt), hex(tgt))] += 1
            else:
                ent = last_lui.get(rs)
                if ent and i - ent[1] <= 6:
                    tgt = ent[0] + imm
                    if SECTIONS[0][1] <= tgt < 0x0016A328:
                        sec = section_of(tgt)
                        abs_targets[sec] += 1
                        if sec in ("sdata", "sbss"):
                            abs_small_data[(sec, hex(tgt))] += 1
            # a load writes rt
            last_lui.pop(rt, None)
        elif op == 0x00:
            # R-type: writes rd
            last_lui.pop(rd, None)
        elif op in WRITES_RT:
            last_lui.pop(rt, None)

    print(f"gp window: [{GP_LO:#x}, {GP_HI:#x}]  _gp={GP:#x}")
    print("\ngp-relative accesses by resolved section:")
    for k, v in gp_targets.most_common():
        print(f"  {k:<8} {v}")
    print(f"\ngp-relative accesses resolving OUTSIDE the window: "
          f"{sum(gp_out_of_window.values())}")
    for (sec, addr), v in gp_out_of_window.most_common(15):
        print(f"  {sec:<8} {addr:<12} {v}")

    print("\nabsolute lui/%lo accesses by resolved section:")
    for k, v in abs_targets.most_common():
        print(f"  {k:<8} {v}")
    print(f"\nabsolute accesses resolving INTO small data (.sdata/.sbss): "
          f"{sum(abs_small_data.values())}")
    for (sec, addr), v in abs_small_data.most_common(15):
        print(f"  {sec:<8} {addr:<12} {v}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
