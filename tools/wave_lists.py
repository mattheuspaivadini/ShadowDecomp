#!/usr/bin/env python3
"""Session 8 wave-list generator.

Reads docs/ledger.json and emits ready-to-draft stem lists, ordered by address
so that address-adjacent functions (likely the same translation unit) land in
the same batch — a confirmed compiler config then propagates.

    python3 tools/wave_lists.py --tier 45-80 --count 48 --out build/s8/w45a.txt
    python3 tools/wave_lists.py --residue --max-score 3 --out build/s8/wres.txt
    python3 tools/wave_lists.py --all --out build/s8/waves   # the whole plan
    python3 tools/wave_lists.py --status                     # tier census
"""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LEDGER = ROOT / "docs" / "ledger.json"

# Reserved: the $gp save/restore family. Plain C cannot emit the dance and the
# EE `as` cannot assemble an inline-asm $gp read (probe: build/s8/probe_gp*.sh),
# so these are held for the Phase-C extended-compiler sweep, not drafted.
RESERVED = {"0092F8", "00A878", "011CA8", "012E80", "016D88", "019AC0", "0171B8"}


def tier_of(n: int) -> str:
    return ("<=24" if n <= 24 else "25-44" if n <= 44 else
            "45-80" if n <= 80 else "81-150" if n <= 150 else ">150")


def load() -> dict:
    return json.loads(LEDGER.read_text(encoding="utf-8"))


def by_addr(recs: list[tuple[str, dict]]) -> list[tuple[str, dict]]:
    return sorted(recs, key=lambda t: int(t[1]["addr"], 16))


def untouched(doc: dict, tier: str | None = None) -> list[tuple[str, dict]]:
    out = [(s, r) for s, r in doc["functions"].items()
           if r["status"] == "untouched" and r["kind"] == "asm"
           and s not in RESERVED]
    if tier:
        out = [(s, r) for s, r in out if tier_of(r["insns"]) == tier]
    return by_addr(out)


def residue(doc: dict, max_score: int) -> list[tuple[str, dict]]:
    out = []
    for s, r in doc["functions"].items():
        m = re.match(r"near\((\d+)\)", r["status"])
        if m and int(m.group(1)) <= max_score:
            out.append((s, r))
    return by_addr(out)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--tier", default=None)
    ap.add_argument("--count", type=int, default=0, help="0 = all")
    ap.add_argument("--out", type=Path, default=None)
    ap.add_argument("--residue", action="store_true")
    ap.add_argument("--max-score", type=int, default=3)
    ap.add_argument("--status", action="store_true")
    ap.add_argument("--all", action="store_true", help="write the full plan")
    args = ap.parse_args()

    doc = load()

    if args.status:
        from collections import Counter
        c = Counter()
        byt = Counter()
        for s, r in doc["functions"].items():
            if r["status"] == "untouched":
                c[tier_of(r["insns"])] += 1
                byt[tier_of(r["insns"])] += r["size"]
        print(f"{'tier':<8} {'funcs':>6} {'bytes':>8}")
        for t in ("<=24", "25-44", "45-80", "81-150", ">150"):
            print(f"{t:<8} {c[t]:>6} {byt[t]:>8}")
        print(f"{'TOTAL':<8} {sum(c.values()):>6} {sum(byt.values()):>8}")
        return 0

    if args.all:
        plan = [
            ("w45a", "45-80", 48), ("w45b", "45-80", 48), ("w25a", "25-44", 48),
            ("w45c", "45-80", 48), ("w25b", "25-44", 48), ("w45d", "45-80", 19),
            ("w8115a", "81-150", 12), ("w8115b", "81-150", 12),
        ]
        used: set[str] = set()
        for name, tier, n in plan:
            pool = [(s, r) for s, r in untouched(doc, tier) if s not in used]
            sel = pool[:n]
            used.update(s for s, _ in sel)
            out = ROOT / "build" / "s8" / f"{name}.txt"
            out.write_text("".join(s + "\n" for s, _ in sel), encoding="utf-8")
            print(f"{name:<8} {tier:<7} {len(sel):>3} stems  {sum(r['size'] for _, r in sel):>6} bytes")
        return 0

    if args.residue:
        pool = residue(doc, args.max_score)
        print(f"residue (score <= {args.max_score}): {len(pool)} stems")
        for s, r in pool:
            print(f"  {s:<8} {r['status']:<9} {r['size']:>4}B")
        if args.out:
            args.out.write_text("".join(s + "\n" for s, _ in pool), encoding="utf-8")
            print(f"wrote {args.out}")
        return 0

    pool = untouched(doc, args.tier)
    sel = pool[:args.count] if args.count else pool
    if args.out:
        args.out.write_text("".join(s + "\n" for s, _ in sel), encoding="utf-8")
    print(f"{len(sel)} stems ({sum(r['size'] for _, r in sel)} bytes)")
    print(" ".join(s for s, _ in sel))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
