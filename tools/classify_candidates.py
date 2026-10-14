#!/usr/bin/env python3
"""Classify the fresh candidate pool (Session 6, step 3):
  * syscall stubs (hand-written SDK asm: keep as .s)
  * tail-call trampolines (a `j` with argument setup)
  * real C candidates, sorted by size.
"""
from __future__ import annotations

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


def body(stem: str):
    text = (ROOT / "asm" / "cod" / f"{stem}.s").read_text(encoding="utf-8", errors="replace")
    m = re.search(r"glabel\s+\S+\n(.*?)endlabel", text, re.S)
    if not m:
        return []
    out = []
    for line in m.group(1).splitlines():
        mm = re.search(r"\*/\s*(.+)$", line)
        if mm and mm.group(1).strip():
            out.append(re.sub(r"\s+", " ", mm.group(1).strip()))
    return out


def main() -> int:
    matched, nm = matched_stems(), {p.stem for p in (ROOT / "src" / "non_matching").glob("*.c")}
    out = subprocess.run(
        [sys.executable, "tools/find_candidates.py", "--all", "--limit", "4000",
         "--max-insns", sys.argv[1] if len(sys.argv) > 1 else "34"],
        cwd=ROOT, capture_output=True, text=True).stdout
    buckets: dict[str, list] = {"syscall": [], "trampoline": [], "real": []}
    for line in out.splitlines():
        m = re.match(r"\s*([0-9A-F]{6})\.s\s+(\S+)\s+(\d+)\s+insn", line)
        if not m:
            continue
        stem, sym, n = m.group(1), m.group(2), int(m.group(3))
        if stem in matched or stem in nm:
            continue
        ins = body(stem)
        if any("syscall" in i for i in ins):
            buckets["syscall"].append((n, stem, sym))
        elif any(re.search(r"\bj\s+func_", i) for i in ins):
            buckets["trampoline"].append((n, stem, sym))
        else:
            buckets["real"].append((n, stem, sym))
    for k, rows in buckets.items():
        rows.sort()
        print(f"### {k}: {len(rows)}")
        for n, stem, sym in rows[:60]:
            print(f"  {stem}  {sym:<22} {n:>3} insn")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
