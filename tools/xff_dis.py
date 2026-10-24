#!/usr/bin/env python3
"""Disassemble one .XFF overlay function with its relocations annotated.

The overlay `.text` is a relocatable image: `lui`/`addiu`/`jal` targets and the
`%gp_rel` offsets are patched by the loader from `.rel.text`. This prints the
R5900 decoding (rabbitizer) with the relocation type and the target symbol next
to the instruction, which is what the C reconstruction needs.

Usage:
    python tools/xff_dis.py KERNEL 000490
    python tools/xff_dis.py KERNEL 000278 --raw
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import xfflib  # noqa: E402

try:
    from rabbitizer import Instruction as R5900Instruction
    from rabbitizer import InstrCategory
except Exception:  # pragma: no cover
    R5900Instruction = None


def decode(word: int, pc: int) -> str:
    if R5900Instruction is None:
        return f".word 0x{word:08x}"
    ins = R5900Instruction(word, pc)
    return ins.disassemble().replace("\t", " ")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("stem")
    ap.add_argument("--raw", action="store_true", help="also print the raw words")
    args = ap.parse_args()

    mod = xfflib.load_module(args.module)
    stem = args.stem.lower().lstrip("0x")
    off = int(stem, 16)
    fn = xfflib.func_bounds(mod, off)
    if fn is None:
        print(f"no symbol at 0x{off:06x}")
        return 1
    start, end, name = fn
    by_off = {r["offset"]: r for r in mod["relocs"] if start <= r["offset"] < end}
    syms = {s["index"]: s for s in mod["symbols"]}
    print(f"/* {mod['module']} 0x{start:06x}..0x{end:06x} {name} ({end - start} B) */")
    for pc in range(start, end, 4):
        word = int.from_bytes(mod["text"][pc:pc + 4], "little")
        note = ""
        r = by_off.get(pc)
        if r is not None:
            tgt = syms.get(r["sym"])
            tname = tgt["name"] if tgt else f"sym#{r['sym']}"
            note = f"   ; {r['field'][0]} {tname}"
        raw = f" {word:08x}" if args.raw else ""
        print(f"  /* {pc:06x}{raw} */  {decode(word, pc):<34}{note}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
