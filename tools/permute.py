#!/usr/bin/env python3
"""Batch source-variant permuter for the Phase-6 loop (Session 5).

Scores every C variant in a directory against one splat function's original
bytes and reports an **instruction-level edit distance** (0 == byte-exact). The
edit distance makes "one instruction closer" visible even when the variant's
size differs from the original, which the strict `tools/matchcheck.py` does not
(it only compares equal-length streams).

    # variants: build/permute/<stem>/<variant>.c  (each a complete C file)
    python3 tools/permute.py 0029C8                    # both pinned compilers
    python3 tools/permute.py 0029C8 --cc 29            # just ee-gcc2.9-991111-01
    python3 tools/permute.py 0029C8 --cc 296 --flags=-g0
    python3 tools/permute.py 0029C8 --note "indexed loop, swapped stores" \
        --log docs/permute-log.md

The score masks the bits that relocation entries patch (the same fields
`tools/matchcheck.py` masks), so `%hi`/`%lo`/`%gp_rel`/`jal` immediates do not
count as differences. Trailing `nop` alignment padding is stripped from both
sides, as in `matchcheck.py`.

`--keep <variant>` copies the chosen variant over `src/non_matching/<stem>.c`
(the caller is responsible for turning it into a proper `src/cod` entry and
re-verifying with `tools/verify_c.py` / `tools/build.py`).
"""
from __future__ import annotations

import argparse
import concurrent.futures
import datetime
import json
import shutil
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import eegcc  # noqa: E402
import matchcheck  # noqa: E402

VARIANTS = ROOT / "build" / "permute"
LOG_HEADER = """# Permutation log (Session 5)

One row per compiled variant. `score` is the instruction edit distance between
the variant and the original (0 == byte-exact, relocation bits masked). The
`verdict` is relative to the best score recorded **before** the row for the same
(stem, compiler) in this file: `kept` = new best, `=best` = tie, `-` otherwise.

| date | stem | cc | variant | score | insns o/m | verdict | note |
|------|------|----|---------|-------|-----------|---------|------|"""


def load_variant_words(obj: Path, symbol: str):
    """(words, masks) of the variant's function, relocation bits masked."""
    o = matchcheck.load_obj(obj)
    start = 0
    for idx, s in o["symbols"].items():
        if s["name"] == symbol:
            start = s["value"]
            break
    else:
        raise ValueError(f"object defines no symbol named {symbol}")
    text = o["text"]
    words = list(struct.unpack(f"<{len(text) // 4}I", text[: len(text) // 4 * 4]))
    masks = [0] * len(words)
    for off, typ, si in o["relocs"]:
        field = matchcheck.REL_FIELD.get(typ)
        if not field:
            continue
        idx = (off - start) // 4
        if off < start or idx >= len(words):
            continue
        masks[idx] |= field[1]
    fwords = words[start // 4:]
    fmasks = masks[start // 4:]
    while fwords and fwords[-1] == 0 and fmasks[-1] == 0:
        fwords.pop()
        fmasks.pop()
    return fwords, fmasks


def edit_distance(orig: list[int], mine: list[int], masks: list[int]):
    """Levenshtein over 32-bit words; masked bits compare equal. Returns (d, back)."""
    n, m = len(orig), len(mine)
    prev = list(range(m + 1))
    back = [[None] * (m + 1) for _ in range(n + 1)]
    for j in range(1, m + 1):
        back[0][j] = ("ins", 0, j - 1)
    for i in range(1, n + 1):
        cur = [i] + [0] * m
        back[i][0] = ("del", i - 1, 0)
        a = orig[i - 1]
        for j in range(1, m + 1):
            b, mask = mine[j - 1], masks[j - 1]
            sub = 0 if ((a ^ b) & ~mask) == 0 else 1
            choices = ((prev[j - 1] + sub, "sub", i - 1, j - 1),
                       (prev[j] + 1, "del", i - 1, j),
                       (cur[j - 1] + 1, "ins", i, j - 1))
            best = min(choices, key=lambda c: c[0])
            cur[j] = best[0]
            back[i][j] = (best[1], best[2], best[3])
        prev = cur
    return prev[m], back


def alignment(back, orig, mine, masks):
    """Walk the DP back-pointers -> (op, orig_word|None, mine_word|None, mask)."""
    out = []
    i, j = len(orig), len(mine)
    while i > 0 or j > 0:
        op, pi, pj = back[i][j]
        if op == "sub":
            eq = ((orig[pi] ^ mine[pj]) & ~masks[pj]) == 0
            out.append(("=" if eq else "!", orig[pi], mine[pj], masks[pj]))
            i, j = pi, pj
        elif op == "ins":
            out.append(("+", None, mine[pj], masks[pj]))
            i, j = pi, pj
        else:
            out.append(("-", orig[pi], None, 0))
            i, j = pi, pj
    out.reverse()
    return out


def best_in_log(log: Path, stem: str, cc: str) -> int | None:
    if not log.exists():
        return None
    best = None
    for line in log.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = [p.strip() for p in line.strip().strip("|").split("|")]
        if len(parts) >= 5 and parts[1] == stem and parts[2] == cc:
            try:
                v = int(parts[4])
            except ValueError:
                continue
            best = v if best is None else min(best, v)
    return best


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stem")
    ap.add_argument("--cc", default="29,296",
                    help="compiler tokens, comma separated (default 29,296)")
    ap.add_argument("--flags", default="",
                    help="extra flags for every compile (per-TU overrides)")
    ap.add_argument("--log", type=Path, default=None,
                    help="append result rows to this markdown file")
    ap.add_argument("--note", default="")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--json", type=Path, default=None)
    ap.add_argument("--keep", default=None,
                    help="copy this variant to src/non_matching/<stem>.c")
    ap.add_argument("--verbose", action="store_true",
                    help="print the aligned diff of every non-matching variant")
    args = ap.parse_args()

    stem = args.stem
    vdir = VARIANTS / stem
    variants = sorted(p for p in vdir.glob("*.c"))
    if not variants:
        print(f"no variants in {vdir}")
        return 2
    ccs = [c.strip() for c in args.cc.split(",") if c.strip()]
    extra = args.flags.split() if args.flags else []
    date = datetime.date.today().isoformat()

    info = matchcheck.parse_asm(stem)
    symbol = info["symbol"]
    rom = matchcheck.load_rom()
    orig = rom[info["addr"] - matchcheck.ROM_BASE:
               info["addr"] - matchcheck.ROM_BASE + info["size"]]
    while len(orig) >= 4 and orig[-4:] == b"\x00\x00\x00\x00":
        orig = orig[:-4]
    owords = list(struct.unpack(f"<{len(orig) // 4}I", orig))

    eegcc.stage_sources()
    wdir = eegcc.WORK / "permute" / stem
    wdir.mkdir(parents=True, exist_ok=True)

    todo = []
    for v in variants:
        shutil.copy2(v, wdir / v.name)
        for cc in ccs:
            todo.append((v, cc))

    def run_one(job):
        v, cc = job
        obj = wdir / "obj" / cc / f"{v.stem}.o"
        obj.parent.mkdir(parents=True, exist_ok=True)
        if obj.exists():
            obj.unlink()
        err = eegcc.compile_c(f"permute/{stem}/{v.name}", obj, extra,
                              compiler=cc, stage=False)
        res = {"variant": v.stem, "cc": cc, "error": err}
        if err:
            return res
        try:
            words, masks = load_variant_words(obj, symbol)
        except ValueError as e:
            res["error"] = str(e)
            return res
        score, back = edit_distance(owords, words, masks)
        res.update(score=score, mine_words=words, masks=masks, back=back)
        return res

    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        results = list(ex.map(run_one, todo))

    log_best: dict[str, int | None] = {}
    if args.log:
        if not args.log.exists():
            args.log.write_text(LOG_HEADER + "\n", encoding="utf-8")
        for cc in ccs:
            log_best[cc] = best_in_log(args.log, stem, cc)
    run_min: dict[str, int] = {}
    for r in results:
        if "score" in r:
            run_min[r["cc"]] = min(run_min.get(r["cc"], 1 << 30), r["score"])

    rows = []
    for r in sorted(results, key=lambda r: (r.get("score", 1 << 30), r["variant"])):
        cc = r["cc"]
        if "score" not in r:
            print(f"  FAIL cc={cc} {r['variant']}: {r['error']}")
            rows.append(f"| {date} | {stem} | {cc} | {r['variant']} | - | -/- | - | "
                        f"compile failed: {r['error']} |")
            continue
        score = r["score"]
        prev = log_best.get(cc)
        if score < run_min[cc]:
            verdict = "**best**"
        elif score == run_min[cc]:
            verdict = "=best"
        else:
            verdict = "-"
        first = f"  {score:>3}  cc={cc:<4} {r['variant']:<28} " \
                f"{len(owords)}/{len(r['mine_words'])} insns"
        print(first + "   <- MATCH" if score == 0 else first)
        if args.verbose and score:
            for op, a, b, _m in alignment(r["back"], owords, r["mine_words"], r["masks"]):
                aw = f"{a:08X}" if a is not None else "        "
                bw = f"{b:08X}" if b is not None else "        "
                if op != "=":
                    print(f"        {op} orig {aw}  mine {bw}")
        rows.append(f"| {date} | {stem} | {cc} | {r['variant']} | {score} | "
                    f"{len(owords)}/{len(r['mine_words'])} | {verdict} | {args.note} |")

    if args.log:
        with args.log.open("a", encoding="utf-8") as fh:
            fh.write("\n".join(rows))
            fh.write("\n")
        print(f"logged {len(rows)} rows to {args.log}")
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(
            [{k: v for k, v in r.items() if k not in ("back", "masks")}
             for r in results], indent=1), encoding="utf-8")

    if args.keep:
        src = vdir / f"{args.keep}.c"
        if not src.exists():
            print(f"--keep: no such variant {src}")
            return 2
        dst = ROOT / "src" / "non_matching" / f"{stem}.c"
        shutil.copy2(src, dst)
        print(f"kept {args.keep}: copied to {dst}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
