#!/usr/bin/env python3
"""Compare the immediate-value multisets of the original function and a
permuter variant (Session 6).

Catches *semantic* mismatches that the instruction edit distance hides inside a
substitution (e.g. 019BE0's `0x200` vs the original `0x2000`, which showed up
only as an ordering diff). Immediates are decoded from the 32-bit words:
I-type immediates (addiu/ori/lui/andi/slti/...), shift amounts and
`mult`/`jal`-free register fields are ignored.

    python3 tools/const_diff.py 019BE0 [variant] [cc]
    python3 tools/const_diff.py --all
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import matchcheck  # noqa: E402
import permute as P  # noqa: E402

IMM_OPS = {
    0x08: "addi", 0x09: "addiu", 0x0A: "slti", 0x0B: "sltiu",
    0x0C: "andi", 0x0D: "ori", 0x0E: "xori", 0x0F: "lui",
    0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu", 0x25: "lhu",
    0x28: "sb", 0x29: "sh", 0x2B: "sw", 0x2F: "cache",
    0x10: "cop0", 0x31: "lwc1", 0x39: "swc1",
    0x04: "beq", 0x05: "bne", 0x06: "blez", 0x07: "bgtz",
    0x01: "regimm",
}
SPECIAL_OPS = {0x00: "sll", 0x02: "srl", 0x03: "sra", 0x3C: "dsll32",
               0x3E: "dsrl32", 0x3F: "dsra32", 0x38: "dsll", 0x3A: "dsrl",
               0x3B: "dsra", 0x18: "mult", 0x1A: "div"}


def immediates(words: list[int], reloc_idx: set[int] | None = None) -> Counter:
    out: Counter = Counter()
    for i, w in enumerate(words):
        if reloc_idx and i in reloc_idx:
            out["RELOC"] += 1
            continue
        if w == 0:  # nop
            continue
        op = w >> 26
        if op == 0:
            funct = w & 0x3F
            if funct in SPECIAL_OPS:
                sa = (w >> 6) & 0x1F
                if funct in (0x00, 0x02, 0x03):
                    out[f"{SPECIAL_OPS[funct]} {sa}"] += 1
                elif funct in (0x3C, 0x3E, 0x3F, 0x38, 0x3A, 0x3B):
                    out[f"{SPECIAL_OPS[funct]} {sa}"] += 1
                else:
                    out[SPECIAL_OPS[funct]] += 1
        elif op in IMM_OPS:
            imm = w & 0xFFFF
            name = IMM_OPS[op]
            if name == "lui":
                out[f"lui {imm:#x}"] += 1
            elif op in (0x04, 0x05, 0x06, 0x07, 0x01, 0x10, 0x2F):
                out[name] += 1  # branch offsets / cache / cop0: not constants
            else:
                s = imm - 0x10000 if imm & 0x8000 else imm
                out[f"{name} {s:#x}"] += 1
    return out


def relocated_indices(stem: str) -> set[int]:
    """Instruction indices whose asm line carries a %hi/%lo/jal relocation."""
    idx: set[int] = set()
    path = ROOT / "asm" / "cod" / f"{stem}.s"
    i = -1
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if not re.search(r"/\* [0-9A-F]{6} [0-9A-F]{8}", line):
            continue
        i += 1
        if "%hi" in line or "%lo" in line or re.search(r"\b(jal|j)\b", line) or "0x" in line.split("*/")[-1]:
            idx.add(i)
    return idx


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stem", nargs="?")
    ap.add_argument("variant", nargs="?", default="v00_baseline")
    ap.add_argument("cc", nargs="?", default="296")
    ap.add_argument("--all", action="store_true")
    args = ap.parse_args()

    rom = matchcheck.load_rom()
    import eegcc
    stems = ([p.stem for p in (ROOT / "src" / "non_matching").glob("*.c")]
             if args.all else [args.stem])
    for stem in sorted(stems):
        info = matchcheck.parse_asm(stem)
        rom_off = info["addr"] - matchcheck.ROM_BASE
        orig = rom[rom_off:rom_off + info["size"]]
        while len(orig) >= 4 and orig[-4:] == b"\x00\x00\x00\x00":
            orig = orig[:-4]
        owords = list(struct.unpack(f"<{len(orig) // 4}I", orig))
        obj = (eegcc.WORK / "permute" / stem / "obj" / f"{args.cc}_default"
               / f"{args.variant}.o")
        if not obj.exists():
            print(f"### {stem}: no object {obj}")
            continue
        try:
            words, masks = P.load_variant_words(obj, info["symbol"])
        except ValueError as exc:
            print(f"### {stem}: {exc}")
            continue
        reloc_mine = {i for i, m in enumerate(masks) if m}
        o = immediates(owords, relocated_indices(stem))
        m = immediates(words, reloc_mine)
        missing = o - m
        extra = m - o
        if not missing and not extra:
            print(f"### {stem}: immediates identical")
            continue
        print(f"### {stem}: (orig {len(owords)} insns, mine {len(words)})")
        if missing:
            print(f"    only in ORIGINAL: {dict(missing)}")
        if extra:
            print(f"    only in OURS    : {dict(extra)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
