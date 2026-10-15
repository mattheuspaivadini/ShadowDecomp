#!/usr/bin/env python3
"""Call-graph view of the unmatched pool (Session 8, Phase D).

For every unmatched function, report how many of its callees are already
matched. A function whose callees are all matched has known signatures and a
known compiler config for its helpers, so it is the cheapest next target
(the bottom-up order). Also reports the reverse: which matched functions are
called by the most unmatched ones (a helper worth understanding once).

    python3 tools/callgraph.py                 # ranked table
    python3 tools/callgraph.py --min-frac 1.0  # only fully-grounded functions
    python3 tools/callgraph.py --json build/s8/callgraph.json
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import shape_clusters as sc  # noqa: E402

LEDGER = ROOT / "docs" / "ledger.json"
CALL = re.compile(r"\b(?:jal|j)\s+(func_[0-9A-Fa-f]+|[a-zA-Z_]\w*)")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--min-frac", type=float, default=0.0)
    ap.add_argument("--max-insns", type=int, default=0)
    ap.add_argument("--json", type=Path, default=None)
    args = ap.parse_args()

    led = json.loads(LEDGER.read_text(encoding="utf-8"))
    matched = {s for s, r in led["functions"].items() if r["status"] == "matched"}

    # stem -> symbol, and symbol -> stem (so callees can be resolved)
    sym2stem: dict[str, str] = {}
    insns: dict[str, int] = {}
    for p in sc.COD.glob("*.s"):
        f = sc.parse(p.stem)
        insns[p.stem] = len(f["insns"])
        if f["symbol"]:
            sym2stem[f["symbol"]] = p.stem

    rows = []
    called_by = defaultdict(list)
    for stem, r in led["functions"].items():
        if r["status"] not in ("untouched",):
            continue
        text = (sc.COD / f"{stem}.s").read_text(encoding="utf-8", errors="replace")
        callees = {m.group(1) for m in CALL.finditer(text)}
        internal = [c for c in callees if c in sym2stem]
        if not internal:
            frac = 1.0
            n_matched = 0
        else:
            n_matched = sum(1 for c in internal if sym2stem[c] in matched)
            frac = n_matched / len(internal)
        for c in internal:
            if sym2stem[c] in matched:
                called_by[sym2stem[c]].append(stem)
        rows.append((frac, len(internal), n_matched, insns.get(stem, 0),
                     r["size"], stem))

    if args.min_frac:
        rows = [x for x in rows if x[0] >= args.min_frac]
    if args.max_insns:
        rows = [x for x in rows if x[3] <= args.max_insns]

    # cheapest first: fully grounded, then fewer callees, then smaller
    rows.sort(key=lambda x: (-x[0], x[1], x[3]))
    print(f"{len(rows)} untouched functions (frac = matched callees / callees)")
    print(f"{'frac':>5} {'callees':>7} {'m':>3} {'insn':>5} {'bytes':>5}  stem")
    for frac, n, m, ins, size, stem in rows[:40]:
        print(f"{frac:>5.2f} {n:>7} {m:>3} {ins:>5} {size:>5}  {stem}")

    print("\nmatched helpers called by the most untouched functions:")
    for sym, callers in sorted(called_by.items(), key=lambda kv: -len(kv[1]))[:10]:
        print(f"  {sym:<20} {len(callers):>3} callers")

    if args.json:
        args.json.write_text(json.dumps(
            [{"stem": s, "frac": f, "callees": n, "matched_callees": m,
              "insns": i, "size": b} for f, n, m, i, b, s in rows],
            indent=1) + "\n", encoding="utf-8")
        print(f"\nwrote {args.json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
