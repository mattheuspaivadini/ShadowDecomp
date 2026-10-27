#!/usr/bin/env python3
"""Inventory the *unnamed* (static) code of the .XFF overlay modules.

The shipped `.symtab` of KERNEL/MANAGER/GAMECORE keeps globals only: every
`static` function was stripped, leaving large gaps between the named functions.
This tool builds a candidate inventory of those functions from evidence that
does not require the symbol table:

  * Ghidra function starts inside a gap (`build/plan/ghidra_out/<MOD>/functions.tsv`);
  * R_MIPS_26 call targets (the addend is stored in the `jal` instruction).

It then reports, per module: gap bytes, candidate count, bytes covered by
candidates, and how many candidates are leaf-shaped (an 8- or 12-byte body that
ends in `jr $ra`), which is the part that can be decompiled mechanically.

Usage:
    python tools/xff_inventory.py                 # all three modules
    python tools/xff_inventory.py KERNEL --list  # print the candidates
"""
from __future__ import annotations

import argparse
import csv
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import xfflib  # noqa: E402

GHIDRA = ROOT / "build" / "plan" / "ghidra_out"


def ghidra_base(module: str, mod: dict) -> int:
    """Module base used by the Ghidra import (derived, not assumed)."""
    path = GHIDRA / module / "functions.tsv"
    rows = list(csv.DictReader(path.open(encoding="utf-8"), delimiter="\t"))
    by_name = {f["name"]: f["st_value"] for f in mod["functions"]}
    votes: dict[int, int] = {}
    for r in rows:
        v = by_name.get(r["name"])
        if v is not None:
            base = int(r["addr"], 16) - v
            votes[base] = votes.get(base, 0) + 1
    return max(votes, key=votes.get) if votes else 0


def segments(mod: dict) -> tuple[list[tuple[int, int]], list[tuple[int, int]]]:
    """(named intervals, gaps) over .text."""
    funcs = sorted(mod["functions"], key=lambda f: f["st_value"])
    named = [(f["st_value"], f["st_value"] + f["size"]) for f in funcs]
    gaps = []
    cur = 0
    for a, b in named:
        if a > cur:
            gaps.append((cur, a))
        cur = max(cur, b)
    if cur < mod["text_size"]:
        gaps.append((cur, mod["text_size"]))
    return named, gaps


def call_targets(mod: dict) -> list[int]:
    """Targets of the R_MIPS_26 relocations (function entries)."""
    out = []
    for r in mod["relocs"]:
        if r["type"] == 4:  # R_MIPS_26
            w = int.from_bytes(mod["text"][r["offset"]:r["offset"] + 4], "little")
            out.append((w & 0x03FFFFFF) << 2)
    return sorted(set(t for t in out if 0 <= t < mod["text_size"] - 8))


def classify(mod: dict, off: int) -> tuple[str, int] | None:
    """(shape, size) for mechanically decompilable leaf functions."""
    t = mod["text"]
    if off + 8 > len(t):
        return None
    w0 = int.from_bytes(t[off:off + 4], "little")
    w1 = int.from_bytes(t[off + 4:off + 8], "little")
    if w0 == 0x03E00008:                     # jr first: 8-byte leaf
        return ("leaf8", 8)
    if w1 == 0x03E00008:                     # one instruction, then jr
        if off + 12 <= len(t):
            w2 = int.from_bytes(t[off + 8:off + 12], "little")
            if w2 == 0:
                return ("leaf12", 12)
    return None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("modules", nargs="*", default=["KERNEL", "MANAGER", "GAMECORE"])
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--csv", type=Path)
    args = ap.parse_args()

    all_rows = []
    for module in (args.modules or ["KERNEL", "MANAGER", "GAMECORE"]):
        mod = xfflib.load_module(module.upper())
        named, gaps = segments(mod)
        base = ghidra_base(mod["module"], mod)
        gh = []
        path = GHIDRA / mod["module"] / "functions.tsv"
        if path.exists():
            for r in csv.DictReader(path.open(encoding="utf-8"), delimiter="\t"):
                gh.append((int(r["addr"], 16) - base, int(r["size"]), r["name"]))
        named_starts = {f["st_value"] for f in mod["functions"]}
        cand = {}
        for off, size, name in gh:
            if off in named_starts:
                continue
            if any(a <= off < b for a, b in gaps):
                cand[off] = {"off": off, "size": size, "name": name, "src": "ghidra"}
        for t in call_targets(mod):
            if t in named_starts:
                continue
            if any(a <= t < b for a, b in gaps):
                cand.setdefault(t, {"off": t, "size": 0, "name": f"func_{t:08X}", "src": "jal"})
        leaves = []
        for off, c in sorted(cand.items()):
            shape = classify(mod, off)
            if shape:
                leaves.append((off, shape[0], shape[1]))
        gap_bytes = sum(b - a for a, b in gaps)
        named_bytes = sum(b - a for a, b in named)
        print(f"== {mod['module']}: .text {mod['text_size']} B, "
              f"{len(mod['functions'])} named ({named_bytes} B), "
              f"{len(gaps)} gaps ({gap_bytes} B)")
        print(f"   candidates in gaps: {len(cand)} "
              f"(ghidra {sum(1 for c in cand.values() if c['src'] == 'ghidra')}, "
              f"jal-only {sum(1 for c in cand.values() if c['src'] == 'jal')})")
        print(f"   mechanically decompilable leaves: {len(leaves)} "
              f"({sum(l[2] for l in leaves)} B)")
        for off in sorted(cand):
            all_rows.append({"module": mod["module"], "offset": f"0x{off:06x}",
                             "shape": (classify(mod, off) or ("?", 0))[0]})
        if args.list:
            by = {(c["off"]): c for c in cand.values()}
            for off, shape, size in leaves:
                print(f"     {off:06x} {size:2d} {shape:7s} {by[off]['name']}")

    if args.csv:
        with args.csv.open("w", encoding="utf-8", newline="\n") as fh:
            w = csv.DictWriter(fh, fieldnames=["module", "offset", "shape"], delimiter="\t")
            w.writeheader()
            w.writerows(all_rows)
        print(f"wrote {args.csv}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
