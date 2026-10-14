#!/usr/bin/env python3
"""Analyse CC matrix JSON files (tools/cc_matrix.py output): per-case coverage
and the minimum set of compilers that covers every matched case.

    python3 tools/cc_matrix_analyze.py build/cc_matrix/matrix.json \
        build/cc_matrix/matrix_wine.json build/cc_matrix/matrix_32-030926.json
"""
from __future__ import annotations

import itertools
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def load(paths: list[str]) -> dict:
    compilers: dict[str, dict] = {}
    cases: list[str] = []
    flags: list[str] = []
    for p in paths:
        M = json.loads(Path(p).read_text())
        flags = flags or M["flag_sets"]
        for c in M["cases"]:
            if c not in cases:
                cases.append(c)
        for sel, d in M["compilers"].items():
            compilers[sel] = d
    return {"cases": cases, "flag_sets": flags, "compilers": compilers}


def main(argv: list[str]) -> int:
    paths = argv[1:] or [str(ROOT / "build" / "cc_matrix" / "matrix.json")]
    M = load(paths)
    cases, comps = M["cases"], list(M["compilers"])

    def ok(sel: str, case: str) -> bool:
        cell = M["compilers"][sel]["cases"][case]
        return any(cell[t]["ok"] for t in M["flag_sets"])

    def why(sel: str, case: str) -> str:
        cell = M["compilers"][sel]["cases"][case]
        for t in M["flag_sets"]:
            if not cell[t]["why"].startswith("compile"):
                return cell[t]["why"]
        return cell[M["flag_sets"][0]]["why"]

    print(f"{len(cases)} cases, {len(comps)} compilers\n")
    uncovered = []
    for case in cases:
        m = [s for s in comps if ok(s, case)]
        if m:
            print(f"  {case:<10} {len(m):>2}x  {' '.join(m)}")
        else:
            uncovered.append(case)
            print(f"  {case:<10} NONE  {why(comps[0], case)}")

    matches = {s: {c for c in cases if ok(s, c)} for s in comps}
    covered = set().union(*matches.values())
    print(f"\nunion coverage: {len(covered)}/{len(cases)}; "
          f"uncovered by ANY compiler: {sorted(set(cases) - covered)}")

    print("\nsingle-compiler totals:")
    for s in sorted(comps, key=lambda x: -len(matches[x])):
        print(f"  {s:<34} {len(matches[s]):>3}/{len(cases)}  "
              f"{M['compilers'][s]['version']}")

    print("\nminimum compiler sets covering the union:")
    for k in range(1, len(comps) + 1):
        found = [c for c in itertools.combinations(comps, k)
                 if len(set().union(*(matches[x] for x in c))) == len(covered)]
        if found:
            for combo in found[:10]:
                print(f"  {combo}")
            print(f"  ({len(found)} minimal combinations of size {k})")
            break
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
