#!/usr/bin/env python3
"""List src/cod/*.c that are not referenced by config/c_sources.txt."""
from __future__ import annotations
import pathlib

root = pathlib.Path(__file__).resolve().parent.parent
man: set[str] = set()
for ln in (root / "config" / "c_sources.txt").read_text().splitlines():
    ln = ln.split("#", 1)[0].strip()
    if "=" in ln:
        man.add(ln.split("=")[0].strip())
cod = sorted(p.stem for p in (root / "src" / "cod").glob("*.c"))
extra = [s for s in cod if s not in man]
print(f"{len(cod)} cod files, {len(extra)} unmatched:")
print(" ".join(extra))
