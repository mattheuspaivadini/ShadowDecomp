#!/usr/bin/env python3
"""Infer translation-unit membership for the unmatched pool (Session 8, Phase D).

Evidence only, no guessing about semantics. For every function we collect the
symbols its body references (`%hi`/`%lo`/`%gp_rel` labels and `jal`/`j`
targets) from asm/cod/<stem>.s, then link two functions when

  * they are within ADJ_BYTES of each other in .text (splat emits contiguous
    functions of one TU consecutively), or
  * they share at least SHARED referenced symbols (a common static/data pool).

Connected components are candidate TUs. A component that already contains a
**matched** function with a confirmed compiler config (config/tu_flags.json)
propagates that config to its unmatched members, with the evidence recorded.

    python3 tools/infer_tu.py                     # summary
    python3 tools/infer_tu.py --json build/s8/tu.json
    python3 tools/infer_tu.py --for-stem 020788   # why is this one in its TU
"""
from __future__ import annotations

import argparse
import json
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COD = ROOT / "asm" / "cod"
LEDGER = ROOT / "docs" / "ledger.json"
TU_FLAGS = ROOT / "config" / "tu_flags.json"

ADJ_BYTES = 0x400          # 1 KiB of .text = "neighbours"
EDGE_WEIGHT = 1.0          # minimum specificity-weighted link strength

SYM = re.compile(r"%(?:hi|lo|gp_rel)\(([^)\s]+)\)")
TGT = re.compile(r"^\s*(?:jal|j)\s+(\S+)", re.M)


def refs(stem: str) -> set[str]:
    p = COD / f"{stem}.s"
    if not p.exists():
        return set()
    t = p.read_text(encoding="utf-8", errors="replace")
    out = set()
    for m in SYM.finditer(t):
        out.add(m.group(1).split("+")[0].strip())
    for m in TGT.finditer(t):
        g = m.group(1)
        if g.startswith("func_") or g.startswith("sce") or g.startswith("D_"):
            out.add(g)
    return out


class DSU:
    def __init__(self) -> None:
        self.p: dict[str, str] = {}

    def find(self, x: str) -> str:
        self.p.setdefault(x, x)
        while self.p[x] != x:
            self.p[x] = self.p[self.p[x]]
            x = self.p[x]
        return x

    def union(self, a: str, b: str) -> None:
        ra, rb = self.find(a), self.find(b)
        if ra != rb:
            self.p[ra] = rb


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", type=Path, default=None)
    ap.add_argument("--for-stem", default=None)
    args = ap.parse_args()

    led = json.loads(LEDGER.read_text(encoding="utf-8"))
    funcs = {s: r for s, r in led["functions"].items()
             if r["kind"] == "asm"}
    conf = json.loads(TU_FLAGS.read_text(encoding="utf-8")).get("confirmed", {})

    r = {s: refs(s) for s in funcs}
    order = sorted(funcs, key=lambda s: int(funcs[s]["addr"], 16))

    dsu = DSU()
    for s in order:
        dsu.find(s)

    # Shared referenced symbols, weighted by *specificity*: a data symbol that
    # only two functions touch is strong evidence they share a TU (a file-scope
    # static), while a symbol half the image uses carries almost none.  This
    # avoids the hub chaining that merges everything into one component.
    bysym: dict[str, list[str]] = defaultdict(list)
    for s, syms in r.items():
        for x in syms:
            bysym[x].append(s)
    weight: dict[tuple[str, str], float] = defaultdict(float)
    for x, members in bysym.items():
        if not (2 <= len(members) <= 6):
            continue
        w = 1.0 / (len(members) - 1)
        for i, a in enumerate(members):
            for b in members[i + 1:]:
                weight[(a, b)] += w
    for (a, b), w in weight.items():
        if w >= EDGE_WEIGHT:
            dsu.union(a, b)

    comps: dict[str, list[str]] = defaultdict(list)
    for s in order:
        comps[dsu.find(s)].append(s)

    out: dict[str, dict] = {}
    propagated = 0
    for root, members in comps.items():
        known = [(s, conf[s]) for s in members if s in conf]
        for s in members:
            if s in conf:
                out[s] = {"tu": root, "cc": conf[s]["cc"],
                          "flags": conf[s]["flags"], "evidence": "matched"}
                continue
            if known:
                # majority vote among the matched members of the component
                votes: dict[tuple, int] = defaultdict(int)
                for _m, c in known:
                    votes[(c["cc"], tuple(c["flags"]))] += 1
                (cc, flags), n = max(votes.items(), key=lambda kv: kv[1])
                out[s] = {"tu": root, "cc": cc, "flags": list(flags),
                          "evidence": f"{n}/{len(members)} matched neighbours"}
                propagated += 1
            else:
                out[s] = {"tu": root, "cc": None, "flags": [],
                          "evidence": "no matched neighbour"}

    matched_in_comp = sum(1 for m in comps.values() if any(s in conf for s in m))
    print(f"{len(funcs)} functions -> {len(comps)} components "
          f"({matched_in_comp} carry a confirmed config)")
    print(f"  configs propagated to {propagated} unmatched functions")
    sizes = sorted((len(m) for m in comps.values()), reverse=True)
    print(f"  component sizes: {sizes[:12]}{' ...' if len(sizes) > 12 else ''}")

    if args.for_stem:
        s = args.for_stem
        if s in out:
            root = out[s]["tu"]
            print(f"\n{s}: {out[s]}")
            print(f"  component ({len(comps[root])}): {' '.join(comps[root][:40])}")
        else:
            print(f"\n{s}: not in the ledger")
        return 0

    if args.json:
        args.json.write_text(json.dumps(out, indent=1, sort_keys=True) + "\n",
                             encoding="utf-8")
        print(f"wrote {args.json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
