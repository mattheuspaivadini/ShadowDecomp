#!/usr/bin/env python3
"""Print the splat .s body of one or more functions (by name or file stem).

Usage:
    python3 tools/show_func.py func_00101A48
    python3 tools/show_func.py 001A48 0032F0
    python3 tools/show_func.py --strip func_00101A48   # instructions only
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COD = ROOT / "asm" / "cod"

GLABEL = re.compile(r"^glabel\s+(\S+)")
INS = re.compile(r"^\s*(?:/\*.*?\*/\s*)(\S+.*)$")


def find(arg: str) -> Path | None:
    p = COD / f"{arg}.s"
    if p.exists():
        return p
    for f in sorted(COD.glob("*.s")):
        for line in f.read_text(encoding="utf-8", errors="replace").splitlines():
            m = GLABEL.match(line)
            if m:
                if m.group(1) == arg:
                    return f
                break
    return None


def main() -> int:
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    strip = "--strip" in sys.argv
    for a in args:
        p = find(a)
        if not p:
            print(f"!! not found: {a}")
            continue
        print(f"===== {a} ({p.relative_to(ROOT)}) =====")
        for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
            if strip:
                if not line.strip().startswith("/*"):
                    continue
            print(line)
        print()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
