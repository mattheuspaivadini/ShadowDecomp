#!/usr/bin/env python3
"""Fresh candidate pool, extended (Session 6, step 3).

Combines:
  * every unmatched function <= N instructions that is NOT in the non-matching
    backlog (from tools/find_candidates.py --all, i.e. including non-leaf code);
  * ranked by (instruction count, call count) so the small/simple ones come
    first.

    python3 tools/fresh_candidates.py --max-insns 60
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def matched_stems() -> set[str]:
    out = set()
    for line in (ROOT / "config" / "c_sources.txt").read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if "=" in line:
            out.add(line.split("=", 1)[0].strip())
    return out


def nm_stems() -> set[str]:
    return {p.stem for p in (ROOT / "src" / "non_matching").glob("*.c")}


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-insns", type=int, default=60)
    ap.add_argument("--min-insns", type=int, default=0)
    args = ap.parse_args()
    matched, nm = matched_stems(), nm_stems()
    out = subprocess.run(
        [sys.executable, "tools/find_candidates.py", "--all", "--limit", "4000",
         "--max-insns", str(args.max_insns)],
        cwd=ROOT, capture_output=True, text=True).stdout
    rows = []
    for line in out.splitlines():
        m = re.match(r"\s*([0-9A-F]{6})\.s\s+(\S+)\s+(\d+)\s+insn(.*)", line)
        if not m:
            continue
        stem, sym, n, rest = m.group(1), m.group(2), int(m.group(3)), m.group(4)
        if stem in matched or stem in nm or n < args.min_insns:
            continue
        calls = int(re.search(r"calls=(\d+)", rest).group(1)) if "calls=" in rest else 0
        rows.append((n, calls, stem, sym))
    rows.sort()
    print(f"{len(rows)} fresh candidates (<= {args.max_insns} insns)")
    for n, calls, stem, sym in rows:
        print(f"  {stem}  {sym:<22} {n:>3} insn calls={calls}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
