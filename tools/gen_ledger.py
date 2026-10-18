#!/usr/bin/env python3
"""Build docs/ledger.json - the single source of truth for Session 8+.

One record per splat subsegment (function), keyed by stem:

    {addr, size, insns, kind, tu, cluster, compiler_cfg,
     status, attempts, notes}

`status` is one of:
    matched         - reproduced byte-exact from C (in config/c_sources.txt)
    near(N)         - a non-matching C attempt with best instruction edit
                      distance N (archived in src/non_matching/)
    asm-permanent   - hand-written body / syscall trampoline (stays .s)
    untouched       - a real C candidate that has never been attempted
    textbin         - a raw-byte subsegment (not a function)

`near` records are enriched from the archived attempt headers (the `STATUS:`
line carries the best score) and the Session-6/7 tables in
docs/non-matching-backlog.md / docs/permute-log.md.

    python3 tools/gen_ledger.py                # write docs/ledger.json
    python3 tools/gen_ledger.py --summary      # also print tier stats
    python3 tools/gen_ledger.py --json out.json
"""
from __future__ import annotations

import argparse
import datetime as _dt
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import shape_clusters as sc  # noqa: E402

NON_MATCHING = ROOT / "src" / "non_matching"
LEDGER = ROOT / "docs" / "ledger.json"

# Functions proven NOT to be plain C, so they stay `.s` permanently.  The `$gp`
# save/restore family: no published EE-GCC generation emits the dance for a C
# indirect call, and the EE `as` cannot assemble an inline-asm `$gp` read
# (build/s8/probe_gp*.sh, sweep_gp*.sh, docs/session8-plan.md).  The MMI string
# primitives are hand-vectorised for the R5900 (`lq`/`psubb`/`pnor`/`pcpyld`/
# `pcpyud`), i.e. not expressible in pure C (project rule: no inline asm).
ASM_PERMANENT_EXTRA = {
    "0092F8": "gp save/restore; no C spelling (probe build/s8/sweep_gp*)",
    "00A878": "gp save/restore; no C spelling (probe build/s8/sweep_gp*)",
    "011CA8": "gp save/restore; no C spelling (probe build/s8/sweep_gp*)",
    "012E80": "gp save/restore; no C spelling (probe build/s8/sweep_gp*)",
    "016D88": "gp save/restore; no C spelling (probe build/s8/sweep_gp*)",
    "019AC0": "gp save/restore; no C spelling (probe build/s8/sweep_gp*)",
    "0171B8": "gp save/restore; no C spelling (probe build/s8/sweep_gp*)",
    "028188": "MMI memcmp: lq/pxor/pcpyud (hand-vectorised)",
    "02821C": "MMI memcpy: lq/sq (hand-vectorised)",
    "0282CC": "MMI memmove: lq/sq (hand-vectorised)",
    "0283D0": "MMI memset: lq/sq (hand-vectorised)",
    "028BB0": "MMI strcat: lq/psubb/pnor/pcpyld/pcpyud (hand-vectorised)",
    "028CDC": "MMI strchr: lq/psubb/pnor/pcpyld/pcpyud/pxor (hand-vectorised)",
    "028E6C": "MMI strcmp: lq/pxor/pcpyud (hand-vectorised)",
    "028FB0": "MMI strcpy: lq/sq/psubb/pnor/pand/pcpyud (hand-vectorised)",
    "0290C4": "MMI strlen: lq/psubb/pnor/pand/pcpyud (hand-vectorised)",
    "029200": "MMI strncmp: lq/pxor/pcpyud (hand-vectorised)",
    "0293B8": "MMI strncpy: lq/sq/psubb/pnor/pand/pcpyud (hand-vectorised)",
    "02E704": "MMI memchr: lq/pxor/pcpyh/pcpyld (hand-vectorised)",
}

# "best score 4 [cc=29, default]" / "best score 14"
SCORE_RE = re.compile(r"best score\s+(\d+)", re.I)
# fallback: the Session-6 machine tables "| 2 | 007C70 | 29 |"
TABLE_ROW = re.compile(r"^\|\s*(\d+)\s*\|\s*([0-9A-Fa-f]{4,6})\b")


def read_scores() -> dict[str, int]:
    """stem -> best known edit distance, from the archived attempt headers
    and the backlog/permute-log tables (header wins when present)."""
    scores: dict[str, int] = {}
    for md in ("docs/non-matching-backlog.md", "docs/permute-log.md"):
        p = ROOT / md
        if not p.exists():
            continue
        for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
            m = TABLE_ROW.match(line)
            if m:
                stem = m.group(2).upper()
                n = int(m.group(1))
                # a table row may list several stems "022BD8 022C30"
                for s in re.findall(r"[0-9A-Fa-f]{4,6}", line.split("|")[2]):
                    s = s.upper()
                    if len(s) >= 4:
                        scores[s] = min(scores.get(s, 99), n)
    for c in sorted(NON_MATCHING.glob("*.c")):
        stem = c.stem.upper()
        m = SCORE_RE.search(c.read_text(encoding="utf-8", errors="replace")[:1200])
        if m:
            scores[stem] = int(m.group(1))
        else:
            scores.setdefault(stem, scores.get(stem, -1))
    return scores


def draft_attempts() -> dict[str, int]:
    """stem -> number of local (gitignored) draft attempts: one per
    `build/*/drafts/<stem>.c` (and `build/*/*/drafts/`) plus one for a
    `build/permute/<stem>/` variant directory.  Without this, a stem with only
    unpromoted, unarchived drafts reads as never attempted."""
    out: dict[str, int] = {}
    for pat in ("build/*/drafts/*.c", "build/*/*/drafts/*.c"):
        for p in ROOT.glob(pat):
            s = p.stem.upper()
            out[s] = out.get(s, 0) + 1
    permute = ROOT / "build" / "permute"
    if permute.is_dir():
        for d in permute.iterdir():
            if d.is_dir():
                s = d.name.upper()
                out[s] = out.get(s, 0) + 1
    return out


def parse_cfg(entry: tuple[str, list[str], str | None]) -> dict:
    """(source, flags, compiler) -> {"source","cc","flags"}."""
    src, flags, compiler = entry
    return {"source": src, "cc": compiler or "296", "flags": list(flags)}


def cluster_map() -> dict[str, int]:
    """stem -> cluster index (only clusters of size >= 3 are informative)."""
    p = ROOT / "build" / "s8" / "clusters.json"
    if not p.exists():
        p = ROOT / "build" / "s7" / "clusters.json"
    if not p.exists():
        return {}
    d = json.loads(p.read_text(encoding="utf-8"))
    out: dict[str, int] = {}
    for i, cl in enumerate(d.get("clusters", [])):
        if cl.get("size", 0) < 3:
            continue
        for s in cl.get("members", []):
            out[s] = i
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--summary", action="store_true")
    ap.add_argument("--json", type=Path, default=LEDGER)
    ap.add_argument("--tu-flags", type=Path, default=None,
                    help="also write config/tu_flags.json from the matched set")
    args = ap.parse_args()

    c_sources = build.load_c_sources()
    c_manifest = build._load_c_manifest()
    subs = build.cod_subsegments()
    scores = read_scores()
    clusters = cluster_map()
    drafts = draft_attempts()

    handwritten = set()
    syscall = set()
    for p in sc.COD.glob("*.s"):
        f = sc.parse(p.stem)
        if f["handwritten"]:
            handwritten.add(p.stem)
        if f["has_syscall"]:
            syscall.add(p.stem)

    archived = {c.stem.upper(): c for c in NON_MATCHING.glob("*.c")}

    funcs: dict[str, dict] = {}
    for vaddr, stem, span, kind in subs:
        if kind not in ("asm", "c", "textbin"):
            continue  # data / rodata / lit4 subsegments are not functions
        if kind == "textbin":
            status = "textbin"
        elif stem in c_sources:
            status = "matched"
        elif stem in archived:
            n = scores.get(stem)
            status = f"near({n})" if n is not None and n >= 0 else "near(?)"
        elif stem in handwritten or stem in syscall or stem in ASM_PERMANENT_EXTRA:
            status = "asm-permanent"
        else:
            status = "untouched"

        insns = 0
        src = sc.COD / f"{stem}.s"
        if src.exists():
            insns = len(sc.parse(stem)["insns"])

        notes = ""
        if stem in syscall:
            notes = "syscall-stub"
        elif stem in handwritten:
            notes = "handwritten"
        elif stem in ASM_PERMANENT_EXTRA:
            notes = ASM_PERMANENT_EXTRA[stem]
        if status.startswith("near") and stem in archived:
            m = SCORE_RE.search(archived[stem].read_text(
                encoding="utf-8", errors="replace")[:1200])
            if m:
                notes = (notes + "; " if notes else "") + f"archived attempt, best {m.group(1)}"

        rec = {
            "addr": f"0x{vaddr:08X}",
            "size": span,
            "insns": insns,
            "kind": kind,
            "tu": None,
            "cluster": clusters.get(stem),
            "compiler_cfg": parse_cfg(c_manifest[stem]) if stem in c_manifest else None,
            "status": status,
            "attempts": (1 if stem in archived else 0) + drafts.get(stem, 0),
            "notes": notes,
        }
        funcs[stem] = rec

    doc = {
        "generated": _dt.datetime.now(_dt.timezone.utc).isoformat(timespec="seconds"),
        "session": 8,
        "gate": {
            "flat_image_size": 237952,
            "flat_image_sha1": "6f853f644a4279db18c15ceb8ee1d2a8b87a7b39",
        },
        "counts": {},
        "functions": funcs,
    }

    from collections import Counter
    c = Counter(r["status"].split("(")[0] for r in funcs.values())
    doc["counts"] = dict(c)
    doc["counts"]["matched_bytes"] = sum(
        r["size"] for r in funcs.values() if r["status"] == "matched")
    doc["counts"]["real_pool_remaining"] = sum(
        1 for r in funcs.values()
        if r["status"] in ("untouched",) or r["status"].startswith("near"))

    args.json.write_text(json.dumps(doc, indent=1, sort_keys=True) + "\n",
                         encoding="utf-8")
    print(f"wrote {args.json}: {len(funcs)} records")
    for k in sorted(doc["counts"]):
        print(f"  {k:<22} {doc['counts'][k]}")

    if args.tu_flags:
        conf = {}
        for stem, r in funcs.items():
            if r["status"] == "matched" and r["compiler_cfg"]:
                conf[stem] = {"cc": r["compiler_cfg"]["cc"],
                              "flags": r["compiler_cfg"]["flags"],
                              "addr": r["addr"], "tu": None}
        args.tu_flags.write_text(json.dumps({
            "_note": "Per-function confirmed EE-GCC config (confirmed only when "
                     "a function is byte-exact under the hash gate). Keyed by "
                     "stem; tu ids are filled by tools/infer_tu.py (Phase D).",
            "confirmed": conf, "tu": {}}, indent=1, sort_keys=True) + "\n",
            encoding="utf-8")
        print(f"wrote {args.tu_flags}: {len(conf)} confirmed configs")

    if args.summary:
        from collections import defaultdict
        agg: dict[str, list[int]] = defaultdict(lambda: [0, 0, 0])
        for stem, r in funcs.items():
            if r["status"] not in ("untouched",) and not r["status"].startswith("near"):
                continue
            n = r["insns"]
            tier = ("<=24" if n <= 24 else "25-44" if n <= 44 else
                    "45-80" if n <= 80 else "81-150" if n <= 150 else ">150")
            attempted = r["status"].startswith("near") or r["attempts"] > 0
            agg[tier][0] += 1
            agg[tier][1] += r["size"]
            agg[tier][2] += 1 if attempted else 0
        print("\n  tier      funcs    bytes  attempted(untouched)")
        for t in ("<=24", "25-44", "45-80", "81-150", ">150"):
            n, b, a = agg[t]
            print(f"  {t:<9} {n:>5} {b:>8}  {a} ({n - a})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
