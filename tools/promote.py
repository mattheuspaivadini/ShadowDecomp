#!/usr/bin/env python3
"""Promote a matching draft into the build.

Copies a draft to src/cod/<stem>.c, strips its leading comment block, writes a
canonical `MATCHED` header, appends the entry to config/c_sources.txt and (if
present) removes the archived src/non_matching/<stem>.c.

    python3 tools/promote.py --spec build/s8/promote-R1-wave3e.txt
    python3 tools/promote.py --stem 002AF0 --cc 296 --note "..." \
        [--from build/s8/drafts/002AF0.c] [--flags "-g0"]

Spec-file format (one promotion per line, `#` comments allowed):

    <stem> <cc> [flags] | <note>
"""
from __future__ import annotations

import argparse
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
C_SOURCES = ROOT / "config" / "c_sources.txt"


def promote(stem: str, cc: str, flags: list[str], note: str,
            src: Path) -> str:
    assert stem.isupper() or re.fullmatch(r"[0-9A-Fa-f]{4,6}", stem), stem
    if not src.exists():
        return f"{stem}: source missing {src}"
    text = src.read_text(encoding="utf-8")
    m = re.match(r"\s*/\*.*?\*/\s*", text, re.S)
    body = text[m.end():] if m else text
    if f"func_" not in body and "D_" not in body:
        return f"{stem}: suspicious body"
    sym = re.search(r"\b(func_[0-9A-Fa-f]+)\s*\(", body)
    header = (f"/* asm/cod/{stem}.s -> {sym.group(1) if sym else stem}.\n"
              f" * {note}\n"
              f" * MATCHED (Session 8). */\n")
    out = ROOT / "src" / "cod" / f"{stem}.c"
    out.write_text(header + body, encoding="utf-8")

    lines = C_SOURCES.read_text(encoding="utf-8").splitlines()
    if any(re.match(rf"^{stem}\s*=", ln) for ln in lines):
        return f"{stem}: already in config/c_sources.txt"
    entry = f"{stem} = src/cod/{stem}.c"
    if cc and cc not in ("296",):
        entry += f" cc={cc}"
    if flags:
        entry += " " + " ".join(flags)
    entry = f"{entry:<46}# {note}"
    lines.append(entry)
    C_SOURCES.write_text("\n".join(lines) + "\n", encoding="utf-8",
                         newline="\n")

    nm = ROOT / "src" / "non_matching" / f"{stem}.c"
    if nm.exists():
        nm.unlink()
    return f"{stem}: promoted (cc={cc}{' ' + ' '.join(flags) if flags else ''})"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--stem")
    ap.add_argument("--cc", default="296")
    ap.add_argument("--flags", default="")
    ap.add_argument("--note", default="")
    ap.add_argument("--from", dest="src", type=Path, default=None)
    ap.add_argument("--spec", type=Path, default=None)
    args = ap.parse_args()

    if args.spec:
        for raw in args.spec.read_text(encoding="utf-8").splitlines():
            line = raw.split("#", 1)[0].strip()
            if not line:
                continue
            left, _, note = line.partition("|")
            parts = left.split()
            stem, cc = parts[0], (parts[1] if len(parts) > 1 else "296")
            flags = parts[2:]
            src = ROOT / "build" / "s8" / "drafts" / f"{stem}.c"
            print(promote(stem, cc, flags, note.strip(), src))
        return 0

    if not args.stem:
        ap.error("need --stem or --spec")
    src = args.src or (ROOT / "build" / "s8" / "drafts" / f"{args.stem}.c")
    print(promote(args.stem, args.cc, args.flags.split(), args.note, src))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
