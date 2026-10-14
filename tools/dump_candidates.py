#!/usr/bin/env python3
"""Dump a candidate list with disassembly, for batch decompilation planning.

    python3 tools/dump_candidates.py --max-insns 14 --limit 60 > build/cands.txt
"""
from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import find_candidates as fc  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-insns", type=int, default=14)
    ap.add_argument("--limit", type=int, default=200)
    args = ap.parse_args()

    cands = [c for c in (fc.analyse(p) for p in sorted(fc.COD.glob("*.s"))) if c]
    pool = [c for c in cands
            if not c["hard"] and c["calls"] == 0 and c["tailcalls"] == 0
            and not c["unaligned"] and c["insns"] <= args.max_insns]
    pool.sort(key=fc.score)
    for c in pool[: args.limit]:
        print(f"===== {c['file'][:-2]} {c['name']} ({c['insns']} insn, "
              f"soft={','.join(c['soft']) or '-'}) =====")
        p = fc.COD / c["file"]
        for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
            if line.lstrip().startswith("/*"):
                print("   " + line.strip())
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
