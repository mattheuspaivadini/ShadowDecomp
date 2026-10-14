#!/usr/bin/env python3
"""Central scoring driver for the wave-based drafting loop (Session 8+).

Copies drafts from a drafts directory (`build/s8/drafts/<stem>.c` by default)
into `build/permute/<stem>/v00_draft.c` and scores every stem with both EE-GCC
generations and the per-TU flag variants:

  cc=29   : default, -g0          (its cc1 rejects -fno-optimize-sibling-calls)
  cc=296  : default, -g0, -fno-optimize-sibling-calls, both combined

Prints a compact best-score table (0 = byte-exact, ready to promote) and
optionally appends the permute-log rows.

    python3 tools/score_drafts.py --stems 0053F0,013228 --note s8-R1
    python3 tools/score_drafts.py --stems-file build/s8/w45a_0.txt --log docs/permute-log.md

(Moved here from `build/s7/score.py`, which is gitignored; the logic is
unchanged apart from the default drafts directory.)
"""
from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def run(cmd: list[str]) -> str:
    r = subprocess.run(cmd, cwd=str(ROOT), capture_output=True, text=True)
    return r.stdout + r.stderr


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--stems", default="")
    ap.add_argument("--stems-file", type=Path, default=None)
    ap.add_argument("--drafts-dir", type=Path,
                    default=ROOT / "build" / "s8" / "drafts",
                    help="directory holding <stem>.c drafts")
    ap.add_argument("--note", default="s8-draft")
    ap.add_argument("--log", type=Path, default=None)
    ap.add_argument("--jobs", type=int, default=8)
    args = ap.parse_args()

    stems = [s.strip() for s in args.stems.split(",") if s.strip()]
    if args.stems_file:
        stems += [ln.strip() for ln in args.stems_file.read_text().splitlines()
                  if ln.strip() and not ln.startswith("#")]
    if not stems:
        print("no stems")
        return 2

    # stage drafts
    staged = []
    for stem in stems:
        src = args.drafts_dir / f"{stem}.c"
        dst = ROOT / "build" / "permute" / stem / "v00_draft.c"
        if not src.exists():
            print(f"  no draft: {src}")
            continue
        dst.parent.mkdir(parents=True, exist_ok=True)
        if not dst.exists() or dst.read_bytes() != src.read_bytes():
            shutil.copy2(src, dst)
        staged.append(stem)
    print(f"scoring {len(staged)} stems: {' '.join(staged)}")
    if not staged:
        print("no drafts found; nothing to score")
        return 2

    base = [sys.executable, "tools/permute_batch.py", "--stems", ",".join(staged),
            "--jobs", str(args.jobs), "--summary"]
    if args.log:
        base += ["--log", str(args.log), "--note", args.note]
    out29 = run(base + ["--cc", "29", "--flag-sets", ";-g0"])
    out296 = run(base + ["--cc", "296", "--flag-sets",
                         ";-g0;-fno-optimize-sibling-calls;-g0 -fno-optimize-sibling-calls"])

    best: dict[str, tuple[int, str, str, str]] = {}
    for line in (out29 + out296).splitlines():
        m = re.match(r"\s*(\d+)\s+(\S+)\s+cc=(\S+)\s+\[([^\]]*)\]\s+(\S+)", line)
        if not m:
            continue
        score, stem, cc, flags, variant = (int(m.group(1)), m.group(2),
                                           m.group(3), m.group(4), m.group(5))
        if stem not in best or score < best[stem][0]:
            best[stem] = (score, cc, flags, variant)

    print(f"\n=== best per stem ({len(best)}) ===")
    for stem in sorted(best, key=lambda s: (best[s][0], s)):
        score, cc, flags, variant = best[stem]
        mark = "  MATCH" if score == 0 else ""
        print(f"  {score:>3}  {stem:<8} cc={cc:<4} [{flags:<26}] {variant}{mark}")

    zeros = [s for s in best if best[s][0] == 0]
    small = [s for s in best if 0 < best[s][0] <= 3]
    print(f"\n{len(zeros)} match: {' '.join(sorted(zeros)) or '-'}")
    print(f"{len(small)} near (<=3): {' '.join(sorted(small)) or '-'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
