#!/usr/bin/env python3
"""Print the STATUS header summary of every src/non_matching/*.c attempt."""
import pathlib
import re

for f in sorted(pathlib.Path("src/non_matching").glob("*.c")):
    lines = f.read_text(encoding="utf-8", errors="replace").splitlines()
    keep = []
    for line in lines[:20]:
        if ("STATUS" in line or "score" in line.lower() or "cc=" in line
                or "family" in line.lower()):
            keep.append(line.strip().strip("/* ").strip())
    print(f"{f.stem} | " + " ; ".join(keep[:4]))
