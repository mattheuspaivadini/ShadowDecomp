#!/usr/bin/env python3
"""Dump compact asm for a batch of stems (Session 6, step 3 helper)."""
from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main() -> int:
    stems = sys.argv[1:]
    if not stems:
        stems = [l.split()[0] for l in sys.stdin.read().splitlines() if l.strip()]
    for stem in stems:
        path = ROOT / "asm" / "cod" / f"{stem}.s"
        text = path.read_text(encoding="utf-8", errors="replace")
        body = re.search(r"glabel\s+\S+\n(.*?)endlabel", text, re.S)
        if not body:
            print(f"=== {stem}: no glabel")
            continue
        insns = []
        for line in body.group(1).splitlines():
            m = re.search(r"\*/\s*(.+)$", line)
            if m and m.group(1).strip():
                insns.append(re.sub(r"\s+", " ", m.group(1).strip()))
        print(f"=== {stem} ({len(insns)} insns)")
        for i in insns:
            print(f"    {i}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
