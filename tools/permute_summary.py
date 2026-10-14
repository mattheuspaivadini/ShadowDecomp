#!/usr/bin/env python3
"""Summarize build/tmp/alldiffs.txt: for each (stem, cc) print the best variant
and its instruction-level diff lines (compact)."""
from __future__ import annotations

import re
import sys
from pathlib import Path

path = Path(sys.argv[1] if len(sys.argv) > 1 else "build/tmp/alldiffs.txt")
lines = path.read_text(encoding="utf-8", errors="replace").splitlines()

row_re = re.compile(r"^\s+(\d+)\s+([0-9A-Fa-f]{6})\s+cc=(\d+)\s+\[([^\]]*)\]\s+(\S+)\s+(\d+)/(\d+) insns")
cur = None
best = {}
order = []
for ln in lines:
    if ln.startswith("=== best score"):
        break
    m = row_re.match(ln)
    if m:
        score, stem, cc, flags, variant = (int(m.group(1)), m.group(2), m.group(3),
                                           m.group(4).strip(), m.group(5))
        cur = (stem, cc, flags)
        order.append(cur)
        best.setdefault(cur, (score, variant, []))
        if score < best[cur][0]:
            best[cur] = (score, variant, [])
        continue
    if cur and ln.startswith("        ") and best[cur][1]:
        if best[cur][2] is None:
            best[cur] = (best[cur][0], best[cur][1], [])
        best[cur][2].append(ln.strip())

# re-walk to attach diffs to the *best* variant only
cur = None
seen = set()
out = {}
for ln in lines:
    if ln.startswith("=== best score"):
        break
    m = row_re.match(ln)
    if m:
        score, stem, cc, flags, variant = (int(m.group(1)), m.group(2), m.group(3),
                                           m.group(4).strip(), m.group(5))
        cur = (stem, cc, flags)
        key = (stem, cc, flags)
        if key not in out:
            out[key] = {"best": (score, variant), "diffs": [], "cur": None}
        if (score, variant) < out[key]["best"]:
            out[key]["best"] = (score, variant)
            out[key]["diffs"] = []
        out[key]["cur"] = (score, variant)
        continue
    if cur and ln.startswith("        ") and out[cur]["cur"] == out[cur]["best"]:
        out[cur]["diffs"].append(ln.strip())

for key in sorted(out, key=lambda k: (out[k]["best"][0], k)):
    stem, cc, flags = key
    score, variant = out[key]["best"]
    print(f"### {stem} cc={cc} [{flags}] best={score} ({variant})")
    for d in out[key]["diffs"][:12]:
        print(f"    {d}")
