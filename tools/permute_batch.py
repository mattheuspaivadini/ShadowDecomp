#!/usr/bin/env python3
"""Batch permuter driver (Session 6).

Runs `tools/permute.py`'s scoring over many stems in one process (one source
staging, one ROM load) and prints a summary table sorted by best score. Used to
baseline the whole `src/non_matching/` backlog and to re-score a batch after new
variants are generated.

    python3 tools/permute_batch.py --baseline            # seed v00 from src/non_matching
    python3 tools/permute_batch.py --note "session6 baseline" --log docs/permute-log.md
    python3 tools/permute_batch.py --stems 002730,00AB58 --verbose
    python3 tools/permute_batch.py --summary             # only print the best scores
"""
from __future__ import annotations

import argparse
import concurrent.futures
import datetime
import json
import re
import shutil
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import eegcc  # noqa: E402
import matchcheck  # noqa: E402
import permute as P  # noqa: E402

VARIANTS = ROOT / "build" / "permute"


def backlog_stems() -> list[str]:
    return sorted(p.stem for p in (ROOT / "src" / "non_matching").glob("*.c"))


def seed_baseline(stem: str) -> str:
    """Copy src/non_matching/<stem>.c to build/permute/<stem>/v00_baseline.c."""
    dst = VARIANTS / stem / "v00_baseline.c"
    src = ROOT / "src" / "non_matching" / f"{stem}.c"
    if not src.exists():
        return f"no such non_matching source: {src}"
    dst.parent.mkdir(parents=True, exist_ok=True)
    if not dst.exists() or dst.read_bytes() != src.read_bytes():
        shutil.copy2(src, dst)
    return ""


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--stems", default="",
                    help="comma-separated stems (default: every src/non_matching/*.c)")
    ap.add_argument("--cc", default="29,296")
    ap.add_argument("--flags", default="")
    ap.add_argument("--flag-sets", default="",
                    help="semicolon-separated flag sets, e.g. "
                         "';-g0;-fno-optimize-sibling-calls' (each tried for "
                         "every variant; the summary reports the best)")
    ap.add_argument("--log", type=Path, default=None)
    ap.add_argument("--note", default="")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--baseline", action="store_true",
                    help="seed build/permute/<stem>/v00_baseline.c from src/non_matching")
    ap.add_argument("--summary", action="store_true", help="print only the best table")
    ap.add_argument("--only", default="",
                    help="comma-separated variant names to compile (default: all)")
    ap.add_argument("--only-contains", default="",
                    help="comma-separated substrings; keep variants whose name "
                         "contains any of them (default: all)")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--json", type=Path, default=None)
    args = ap.parse_args()

    stems = ([s.strip() for s in args.stems.split(",") if s.strip()]
             if args.stems else backlog_stems())
    stems = list(dict.fromkeys(stems))  # dedupe: duplicate stems race on unlink
    only = {s.strip() for s in args.only.split(",") if s.strip()}
    only_contains = [s.strip() for s in args.only_contains.split(",") if s.strip()]
    ccs = [c.strip() for c in args.cc.split(",") if c.strip()]
    if args.flag_sets:
        flag_sets = [[f for f in s.split() if f] for s in args.flag_sets.split(";")]
        flag_sets = [list(t) for t in dict.fromkeys(tuple(fs) for fs in flag_sets)]
    else:
        flag_sets = [args.flags.split() if args.flags else []]
    date = datetime.date.today().isoformat()

    if args.baseline:
        for s in stems:
            err = seed_baseline(s)
            if err:
                print(f"  baseline: {err}")

    rom = matchcheck.load_rom()
    eegcc.stage_sources()

    jobs = []
    info_cache = {}
    for stem in stems:
        vdir = VARIANTS / stem
        variants = sorted(p for p in vdir.glob("*.c"))
        if only:
            variants = [p for p in variants if p.stem in only]
        if only_contains:
            variants = [p for p in variants
                        if any(s in p.stem for s in only_contains)]
        if not variants:
            print(f"  no variants in {vdir} (use --baseline)")
            continue
        info = matchcheck.parse_asm(stem)
        info_cache[stem] = info
        wdir = eegcc.WORK / "permute" / stem
        wdir.mkdir(parents=True, exist_ok=True)
        for v in variants:
            shutil.copy2(v, wdir / v.name)
            for cc in ccs:
                for fs in flag_sets:
                    jobs.append((stem, v, cc, wdir, fs))

    print(f"{len(jobs)} compiles over {len(info_cache)} stems")

    def flag_tag(fs):
        return " ".join(fs) if fs else "default"

    def run_one(job):
        stem, v, cc, wdir, fs = job
        tag = re.sub(r"[^A-Za-z0-9]+", "_", flag_tag(fs))
        obj = wdir / "obj" / f"{cc}_{tag}" / f"{v.stem}.o"
        obj.parent.mkdir(parents=True, exist_ok=True)
        if obj.exists():
            obj.unlink()
        err = eegcc.compile_c(f"permute/{stem}/{v.name}", obj, fs,
                              compiler=cc, stage=False)
        res = {"stem": stem, "variant": v.stem, "cc": cc, "flags": flag_tag(fs),
               "error": err}
        if err:
            return res
        info = info_cache[stem]
        try:
            words, masks = P.load_variant_words(obj, info["symbol"])
        except ValueError as e:
            res["error"] = str(e)
            return res
        rom_off = info["addr"] - matchcheck.ROM_BASE
        orig = rom[rom_off:rom_off + info["size"]]
        while len(orig) >= 4 and orig[-4:] == b"\x00\x00\x00\x00":
            orig = orig[:-4]
        owords = list(struct.unpack(f"<{len(orig) // 4}I", orig))
        score, back = P.edit_distance(owords, words, masks)
        res.update(score=score, mine_words=words, masks=masks, back=back,
                   owords=owords)
        return res

    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        results = list(ex.map(run_one, jobs))

    best: dict[tuple[str, str, str], int] = {}
    best_variant: dict[tuple[str, str, str], str] = {}
    for r in results:
        if "score" not in r:
            continue
        key = (r["stem"], r["cc"], r["flags"])
        if key not in best or r["score"] < best[key]:
            best[key] = r["score"]
            best_variant[key] = r["variant"]

    if not args.summary:
        rows = []
        for r in sorted(results, key=lambda r: (r["stem"], r.get("score", 1 << 30), r["variant"])):
            stem, cc = r["stem"], r["cc"]
            if "score" not in r:
                print(f"  FAIL {stem} cc={cc} {r['variant']}: {r['error']}")
                rows.append(f"| {date} | {stem} | {cc} | {r['variant']} | - | -/- | - | "
                            f"compile failed: {r['error']} |")
                continue
            tag = ""
            if r["score"] == best[(stem, cc, r["flags"])]:
                tag = "  <- best"
            if r["score"] == 0:
                tag = "  <- MATCH"
            print(f"  {r['score']:>3}  {stem:<7} cc={cc:<4} [{r['flags']:<28}] {r['variant']:<30} "
                  f"{len(r['owords'])}/{len(r['mine_words'])} insns{tag}")
            if args.verbose and r["score"]:
                for op, a, b, _m in P.alignment(r["back"], r["owords"], r["mine_words"], r["masks"]):
                    aw = f"{a:08X}" if a is not None else "        "
                    bw = f"{b:08X}" if b is not None else "        "
                    if op != "=":
                        print(f"        {op} orig {aw}  mine {bw}")
            rows.append(f"| {date} | {stem} | {cc} | {r['variant']} | {r['score']} | "
                        f"{len(r['owords'])}/{len(r['mine_words'])} | {tag.strip() or '-'} | "
                        f"{args.note} [{r['flags']}] |")
        if args.log:
            if not args.log.exists():
                args.log.write_text(P.LOG_HEADER + "\n", encoding="utf-8")
            with args.log.open("a", encoding="utf-8") as fh:
                fh.write("\n".join(rows))
                fh.write("\n")
            print(f"logged {len(rows)} rows to {args.log}")

    print("\n=== best score per (stem, cc, flags) ===")
    order = sorted(best, key=lambda k: (best[k], k[0], k[1]))
    for stem, cc, flags in order:
        v = best_variant[(stem, cc, flags)]
        print(f"  {best[(stem, cc, flags)]:>3}  {stem:<7} cc={cc:<4} [{flags:<28}] {v}")
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(
            {"best": {f"{k[0]}/{k[1]}/{k[2]}": v for k, v in best.items()},
             "variants": {f"{k[0]}/{k[1]}/{k[2]}": v for k, v in best_variant.items()}},
            indent=1), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
