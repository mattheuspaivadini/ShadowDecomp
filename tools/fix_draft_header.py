#!/usr/bin/env python3
"""Sanitise a draft's leading header comment: neutralise *nested* `/* ... */`
sequences (C has no nested comments, so an inner `*/` terminates the header and
the rest of it becomes invalid code).

The outer `/*` opener and the final `*/` terminator are preserved; every inner
`/*`/`*/` is rewritten to `(`/`)`. Also repairs files damaged by the first
version of this tool (a leading `(` where the `/*` opener should be).

    python3 tools/fix_draft_header.py build/s8/drafts/*.c
    python3 tools/fix_draft_header.py --check build/s8/drafts/0117B0.c
"""
from __future__ import annotations

import argparse
from pathlib import Path


def find_header(lines: list[str]) -> tuple[int, int] | None:
    """(start, end_exclusive) line indices of the leading block comment."""
    start = None
    for i, ln in enumerate(lines):
        if ln.lstrip().startswith("/*") or ln.lstrip().startswith("( "):
            start = i
            break
    if start is None:
        return None
    for i in range(start, len(lines)):
        if "*/" not in lines[i]:
            continue
        nxt = next((l for l in lines[i + 1:] if l.strip()), "")
        if not nxt.strip().startswith("*"):
            return start, i + 1
    return None


def fix(text: str) -> tuple[str, bool]:
    lines = text.splitlines(keepends=True)
    if not lines:
        return text, False
    changed = False

    # repair the opener damaged by the first version of this tool
    if lines[0].lstrip().startswith("( ") and "*/" in text:
        lines[0] = lines[0].replace("( ", "/*", 1)
        changed = True

    span = find_header(lines)
    if span is None:
        return "".join(lines), changed
    start, end = span

    # rebuild the header: keep the first `/*` and the last `*/`
    head = "".join(lines[start:end])
    first = head.find("/*")
    last = head.rfind("*/")
    if first < 0 or last <= first:
        return "".join(lines), changed
    inner = head[first + 2:last]
    if "/*" in inner or "*/" in inner:
        inner = inner.replace("/*", "(").replace("*/", ")")
        changed = True
    new_head = head[:first] + "/*" + inner + "*/" + head[last + 2:]
    return "".join(lines[:start]) + new_head + "".join(lines[end:]), changed


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("files", nargs="+", type=Path)
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    n = 0
    for p in args.files:
        t = p.read_text(encoding="utf-8", errors="replace")
        new, changed = fix(t)
        if changed:
            n += 1
            if args.check:
                print(f"{p}: NEEDS FIX")
            else:
                p.write_text(new, encoding="utf-8")
                print(f"{p}: fixed")
    print(f"{n} file(s) changed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
