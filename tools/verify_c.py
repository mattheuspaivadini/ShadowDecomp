#!/usr/bin/env python3
"""Verify every C source in config/c_sources.txt against the original bytes.

This is the *entry gate* for adding a function to the manifest: it compiles the
C in isolation and compares its instructions with the original function, with
relocation fields masked (tools/matchcheck.py). It is stricter than the
whole-image hash check because it reports per-function and per-instruction
differences, and it does not require an object to be 100 % sized correctly.

    python3 tools/verify_c.py                 # all manifest entries
    python3 tools/verify_c.py 002FE0 011FB8   # selected stems
    python3 tools/verify_c.py --verbose
"""
from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402
import eegcc  # noqa: E402
import matchcheck  # noqa: E402

TMP = eegcc.WORK / "obj" / "verify"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--json", type=Path)
    ap.add_argument("--flags", default=None,
                    help="extra flags for every stem (overrides the manifest; "
                         "used to try a per-TU -g level before listing it)")
    args = ap.parse_args()
    extra = args.flags.split() if args.flags else None

    c_sources = build.load_c_sources()
    stems = args.stems or sorted(c_sources)
    rom = matchcheck.load_rom()
    if TMP.exists():
        shutil.rmtree(TMP)
    TMP.mkdir(parents=True, exist_ok=True)

    ok_n = 0
    import json
    results = []
    for stem in stems:
        src = c_sources.get(stem)
        if src is None:
            cand = Path("src") / "cod" / f"{stem}.c"
            if not cand.exists():
                print(f"{stem}: not in config/c_sources.txt")
                continue
            src = str(cand).replace("\\", "/")
        obj = TMP / f"{stem}.o"
        err = eegcc.compile_c(src, obj, extra if extra is not None
                              else build.load_c_flags(stem))
        if err:
            print(f"FAIL  {stem}: compile: {err}")
            results.append({"stem": stem, "ok": False, "why": err})
            continue
        r = matchcheck.compare(obj, stem, rom, verbose=args.verbose)
        results.append(r)
        if r["ok"]:
            ok_n += 1
            print(f"MATCH {stem} {r['symbol']} code={r['code_size']}B "
                  f"pad={r['pad_bytes']}B relocs={len(r['relocs'])}")
        else:
            print(f"DIFF  {stem} {r['symbol']}: {r.get('why', '?')}")
            for d in r.get("diffs", [])[:8]:
                print(f"        +{d['off']:#04x} orig {d['orig']} mine {d['mine']}")
    print(f"-- {ok_n}/{len(stems)} byte-exact")
    if args.json:
        args.json.write_text(json.dumps(results, indent=1), encoding="utf-8")
    return 0 if ok_n == len(stems) else 1


if __name__ == "__main__":
    sys.exit(main())
