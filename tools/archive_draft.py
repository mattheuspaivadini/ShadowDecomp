#!/usr/bin/env python3
"""Archive a non-matching Session-8 draft into src/non_matching/.

    python3 tools/archive_draft.py --stem 0155D8 --score 2 --cc 29 \
        --note "rotated-loop: preheader sb + bgezl delay copy"
    python3 tools/archive_draft.py --spec build/s8/archive-R1.txt

Spec line:  <stem> <score> <cc> [flags] | <note>
"""
from __future__ import annotations

import argparse
import datetime as _dt
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DRAFTS = ROOT / "build" / "s8" / "drafts"
NM = ROOT / "src" / "non_matching"


def archive(stem: str, score: str, cc: str, flags: list[str], note: str,
            src: Path) -> str:
    if not src.exists():
        return f"{stem}: draft missing {src}"
    text = src.read_text(encoding="utf-8")
    m = re.match(r"\s*/\*.*?\*/\s*", text, re.S)
    body = text[m.end():] if m else text
    flagstr = (" " + " ".join(flags)) if flags else ""
    head = (f"/* STATUS (Session 8, {_dt.date.today().isoformat()}): "
            f"NON_MATCHING. best score {score} [cc={cc}{flagstr}].\n"
            f" * {note}\n"
            f" * The original .s stays in the build (asm/cod/{stem}.s); this C\n"
            f" * draft (Session 8) is kept for the record. */\n")
    NM.mkdir(parents=True, exist_ok=True)
    (NM / f"{stem}.c").write_text(head + body, encoding="utf-8")
    return f"{stem}: archived (score {score}, cc={cc}{flagstr})"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--stem")
    ap.add_argument("--score", default="?")
    ap.add_argument("--cc", default="296")
    ap.add_argument("--flags", default="")
    ap.add_argument("--note", default="")
    ap.add_argument("--spec", type=Path, default=None)
    args = ap.parse_args()

    if args.spec:
        for raw in args.spec.read_text(encoding="utf-8").splitlines():
            line = raw.split("#", 1)[0].strip() if not raw.lstrip().startswith("|") else raw.strip()
            if not line:
                continue
            left, _, note = line.partition("|")
            parts = left.split()
            if len(parts) < 2:
                continue
            stem, score = parts[0], parts[1]
            cc = parts[2] if len(parts) > 2 else "296"
            flags = parts[3:]
            print(archive(stem, score, cc, flags, note.strip(), DRAFTS / f"{stem}.c"))
        return 0

    if not args.stem:
        ap.error("need --stem or --spec")
    print(archive(args.stem, args.score, args.cc, args.flags.split(),
                  args.note, DRAFTS / f"{args.stem}.c"))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
