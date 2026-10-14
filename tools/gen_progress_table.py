#!/usr/bin/env python3
"""Emit the matched-function markdown table for docs/progress.md."""
from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))

import report  # noqa: E402


def main() -> int:
    import io
    buf = io.StringIO()
    old = sys.stdout
    sys.stdout = buf
    # report.main() prints the human summary; the JSON path is easier:
    sys.stdout = old
    out = subprocess.run([sys.executable, str(ROOT / "tools" / "report.py"),
                          "--json"], capture_output=True, text=True,
                         cwd=ROOT)
    d = json.loads(out.stdout)
    print(f"| # | Address | Size | Source |")
    print(f"|---|---------|------|--------|")
    for i, f in enumerate(d["functions"], 1):
        print(f"| {i} | {f['address']} | {f['size']} | `src/cod/{f['stem']}.c` |")
    print()
    print(f"functions_matched_c: {d['functions_matched_c']}")
    print(f"text_bytes_matched: {d['text_bytes_matched']}")
    print(f"matched_percent: {d['matched_percent']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
