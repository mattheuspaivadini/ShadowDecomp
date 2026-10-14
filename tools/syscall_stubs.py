#!/usr/bin/env python3
"""Find every unmatched function of the shape
    addiu $v1,$zero,N ; syscall 0 ; jr $ra ; nop
(the PS2 syscall-stub family) and report the N values + stems."""
from __future__ import annotations

import re
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


def main() -> int:
    matched = matched_stems()
    nm = {p.stem for p in (ROOT / "src" / "non_matching").glob("*.c")}
    hits = []
    for p in sorted((ROOT / "asm" / "cod").glob("*.s")):
        text = p.read_text(encoding="utf-8", errors="replace")
        m = re.search(
            r"glabel\s+(\S+)\n"
            r"\s+/\* \S+ \S+ ([0-9A-F]{8}) \*/\s+addiu\s+\$v1, \$zero, (0x[0-9A-Fa-f]+|\d+)\n"
            r"\s+/\* \S+ \S+ [0-9A-F]{8} \*/\s+syscall",
            text)
        if not m:
            continue
        stem = p.stem
        hits.append((stem, m.group(1), m.group(3), stem in matched, stem in nm))
    todo = [h for h in hits if not h[3]]
    print(f"{len(hits)} syscall stubs total, {len(todo)} unmatched "
          f"({sum(1 for h in todo if h[4])} already in the backlog)")
    for stem, sym, n, _m, in_nm in todo:
        flag = " (backlog)" if in_nm else ""
        print(f"  {stem}  {sym:<22} syscall {n}{flag}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
