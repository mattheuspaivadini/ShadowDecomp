#!/usr/bin/env python3
"""Discriminate the optimisation level: sweep `-O` over the C we have.

Compiles each function (the manifest entries by default, or explicit stems) at
several optimisation levels while keeping the *per-TU* flags from
`config/c_sources.txt` (the `-g` level and `-fno-optimize-sibling-calls`) and the
per-TU compiler revision (`cc=29`). The explicit `-O...` replaces the pinned
`-O2` (tools/eegcc.py:cflags_for), so each row is a clean single-level build.

A function that matches the original at exactly one level discriminates `-O`.
Runs inside WSL2 (needs `tools/cc/eegcc.sh` and build/SCUS_974.72.rom).

    python3 tools/opt_sweep.py                       # manifest, all levels
    python3 tools/opt_sweep.py 006B58 0148E0        # selected stems
    python3 tools/opt_sweep.py --levels '-O1 -O2'    # chosen levels
    python3 tools/opt_sweep.py --non-matching        # also src/non_matching/
"""
from __future__ import annotations

import argparse
import json
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402
import eegcc  # noqa: E402
import matchcheck  # noqa: E402

TMP = eegcc.WORK / "obj" / "optsweep"
DEFAULT_LEVELS = ["-O1", "-O2", "-O3", "-Os"]


def find_source(stem: str) -> Path | None:
    c = Path("src") / "cod" / f"{stem}.c"
    if c.exists():
        return c
    c = Path("src") / "non_matching" / f"{stem}.c"
    if c.exists():
        return c
    return None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--levels", default=" ".join(DEFAULT_LEVELS),
                    help="space-separated -O spellings to sweep")
    ap.add_argument("--non-matching", action="store_true",
                    help="include every src/non_matching/*.c stem")
    ap.add_argument("--compiler", default=None,
                    help="override the compiler token for every stem (e.g. 29)")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--json", type=Path,
                    default=ROOT / "build" / "opt_sweep" / "results.json")
    args = ap.parse_args()

    levels = args.levels.split()
    c_sources = build.load_c_sources()
    if args.stems:
        stems = args.stems
    else:
        stems = sorted(c_sources)
    if args.non_matching:
        extra = sorted(p.stem for p in (ROOT / "src" / "non_matching").glob("*.c"))
        stems = sorted(set(stems) | set(extra))

    rom = matchcheck.load_rom()
    eegcc.stage_sources()  # once; compile_c(stage=False) otherwise re-mirrors
    if TMP.exists():
        shutil.rmtree(TMP)
    TMP.mkdir(parents=True, exist_ok=True)

    rows: list[dict] = []
    col_of: dict[str, dict[str, bool]] = {}
    print(f"{'stem':<8} {'size':>4} {'comp':<8} " + " ".join(
        f"{lv:>11}" for lv in levels))
    for stem in stems:
        src = find_source(stem)
        if src is None:
            print(f"{stem}: no source found")
            continue
        src_rel = str(src).replace("\\", "/")
        per_flags = build.load_c_flags(stem)
        compiler = args.compiler if args.compiler is not None \
            else build.load_c_compiler(stem)
        marks: dict[str, str] = {}
        row = {"stem": stem, "symbol": matchcheck.parse_asm(stem)["symbol"],
               "size": matchcheck.parse_asm(stem)["size"],
               "levels": {}}
        for lv in levels:
            obj = TMP / f"{stem}{lv.replace(' ', '_')}.o"
            err = eegcc.compile_c(src_rel, obj, per_flags + lv.split(),
                                  compiler=compiler, stage=False)
            if err:
                marks[lv] = "CFAIL"
                row["levels"][lv] = {"ok": False, "why": f"compile: {err}"}
                continue
            r = matchcheck.compare(obj, stem, rom, verbose=args.verbose)
            nd = len(r.get("diffs", []))
            marks[lv] = "MATCH" if r["ok"] else f"-{nd}" if "diffs" in r else "SDIFF"
            row["levels"][lv] = {"ok": r["ok"],
                                 "ndiff": nd,
                                 "why": r.get("why")}
        rows.append(row)
        col_of[stem] = {lv: row["levels"][lv]["ok"] for lv in levels}
        try:
            print(f"{stem:<8} {str(row['size']):>4} "
                  f"{(compiler or 'default'):<8} "
                  + " ".join(f"{marks[lv]:>11}" for lv in levels))
        except OSError:
            pass

    print()
    # verdict summary
    disc: dict[str, list[str]] = {lv: [] for lv in levels}
    for stem, ok in col_of.items():
        for lv in levels:
            if ok[lv]:
                disc[lv].append(stem)
    print(f"\nlevel summary over {len(rows)} functions:")
    for lv in levels:
        print(f"  {lv:<28} matched {len(disc[lv]):>3}/{len(rows)}")

    best = max((len(disc[lv]) for lv in levels), default=0)
    survivors = [lv for lv in levels if len(disc[lv]) == best]
    for lv in levels:
        if len(disc[lv]) == best:
            continue
        # functions that match at a surviving level but NOT at this level
        n = 0
        example = None
        for s in rows:
            if not s["levels"][lv]["ok"] and any(
                    s["levels"][o]["ok"] for o in survivors):
                n += 1
                example = example or s["stem"]
        print(f"  RULED OUT {lv:<14} {n} function(s) match at "
              f"{'/'.join(survivors)} but not here (e.g. {example})")
    if len(survivors) == 1:
        print(f"VERDICT: {survivors[0]} is the only level consistent with the "
              f"corpus ({best}/{len(rows)} functions)")
    else:
        print(f"VERDICT: not separated - {' and '.join(survivors)} match the same "
              f"{best}/{len(rows)} functions (codegen-identical here)")

    unique = [stem for stem, ok in col_of.items()
              if sum(1 for lv in levels if ok[lv]) == 1]
    if unique:
        print(f"\nfunctions that match at exactly one level:")
        for lv in levels:
            sel = [s for s in unique if col_of[s][lv]]
            if sel:
                print(f"  {lv:<12} {len(sel):>2}: {' '.join(sel)}")

    args.json.parent.mkdir(parents=True, exist_ok=True)
    args.json.write_text(json.dumps({"levels": levels, "rows": rows}, indent=1),
                         encoding="utf-8")
    print(f"wrote {args.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
