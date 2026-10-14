#!/usr/bin/env python3
"""List leaf candidates (from find_candidates) that are not yet in the manifest.

    python3 tools/list_unmatched.py [--max-insns 16]
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import find_candidates as fc  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent


def matched_stems() -> set[str]:
    out: set[str] = set()
    for ln in (ROOT / "config" / "c_sources.txt").read_text().splitlines():
        ln = ln.strip()
        if not ln or ln.startswith("#"):
            continue
        out.add(ln.split("=")[0].strip())
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-insns", type=int, default=16)
    args = ap.parse_args()
    matched = matched_stems()
    cands = [c for c in (fc.analyse(p) for p in sorted(fc.COD.glob("*.s"))) if c]
    pool = [c for c in cands
            if not c["hard"] and c["calls"] == 0 and c["tailcalls"] == 0
            and not c["unaligned"] and c["insns"] <= args.max_insns]
    pool.sort(key=fc.score)
    un = [c for c in pool if c["file"][:-2] not in matched]
    print(f"{len(un)} unmatched candidates (<= {args.max_insns} insns)")
    for c in un:
        print(f"{c['file'][:-2]:<8} {c['name']:<18} {c['insns']:>3} insn "
              f"soft={','.join(c['soft']) or '-'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
