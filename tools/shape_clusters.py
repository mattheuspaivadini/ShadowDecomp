#!/usr/bin/env python3
"""Cluster the remaining (unmatched) functions by normalized instruction shape.

Session 7 step 1: recognise *families* of identical shapes instead of
decompiling one function at a time. For every `asm/cod/*.s` that is not in
`config/c_sources.txt` this tool:

  * normalizes each instruction to a shape token (registers kept, immediates
    abstracted to `#`, relocation symbols to `%hi`/`%lo`, branch targets to
    `L<k>` and call targets to `C<k>` by order of first appearance);
  * clusters the unmatched functions by full token sequence;
  * finds *exact clones* of already-matched functions (the same signature -
    those are near-zero marginal cost: copy the matched C, adapt the
    symbols/constants);
  * classifies hand-written / syscall-stub code (kept as `.s`, not counted).

Output: a ranked table of clusters (size, smallest member, member list) and
the clone table, plus optional JSON for downstream scripting.

    python3 tools/shape_clusters.py
    python3 tools/shape_clusters.py --min-cluster 2 --json build/s7/clusters.json
    python3 tools/shape_clusters.py --stems 010910,011F90   # inspect one group
"""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COD = ROOT / "asm" / "cod"

LINE = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/\s*(\S+)(?:\s+(.*?))?\s*$"
)

REG = re.compile(r"^\$[a-z0-9]+$")
IMM = re.compile(r"^-?(0x[0-9A-Fa-f]+|\d+)$")
TARGET = re.compile(r"^(\.L[0-9A-Fa-f]+|func_[0-9A-Fa-f]+|[A-Za-z_][\w.]*)$")


def matched_map() -> dict[str, str]:
    """stem -> cc token ('' = default) for every manifest entry."""
    out: dict[str, str] = {}
    for line in (ROOT / "config" / "c_sources.txt").read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        m = re.match(r"^([0-9A-F]{4,6})\s*=\s*(\S+)(.*)$", line)
        if not m:
            continue
        cc = ""
        cm = re.search(r"cc=(\w+)", m.group(3))
        if cm:
            cc = cm.group(1)
        out[m.group(1)] = cc
    return out


def parse(stem: str) -> dict:
    text = (COD / f"{stem}.s").read_text(encoding="utf-8", errors="replace")
    m = re.search(r"glabel\s+(\S+)\n(.*?)endlabel", text, re.S)
    if not m:
        return {"stem": stem, "symbol": None, "insns": [], "handwritten": False}
    insns = []
    for line in m.group(2).splitlines():
        mm = LINE.match(line)
        if mm and not mm.group(2).startswith(".word"):
            insns.append((mm.group(2), (mm.group(3) or "").strip()))
    return {
        "stem": stem,
        "symbol": m.group(1),
        "insns": insns,
        "handwritten": "Handwritten function" in text,
        "has_syscall": any(mn == "syscall" for mn, _ in insns),
    }


def normalize(fn: dict) -> tuple[str, ...]:
    """Instruction sequence -> canonical shape tokens."""
    labels: dict[str, str] = {}
    calls: dict[str, str] = {}

    def norm_operand(op: str, mnem: str, is_target_pos: bool) -> str:
        op = op.strip()
        if not op:
            return op
        # memory form: offset($reg)
        mo = re.match(r"^(-?0x[0-9A-Fa-f]+|\d+)\((\$[a-z0-9]+)\)$", op)
        if mo:
            return f"#({mo.group(2)})"
        if REG.match(op):
            return op
        hi = re.match(r"^%(hi|lo|gp_rel)\((.*)\)$", op)
        if hi:
            return f"%{hi.group(1)}"
        if IMM.match(op):
            return "#"
        if is_target_pos and (mnem in ("j", "jal") or mnem.startswith("b")):
            if op.startswith(".L"):
                if op not in labels:
                    labels[op] = f"L{len(labels)}"
                return labels[op]
            if mnem in ("j", "jal"):
                if op not in calls:
                    calls[op] = f"C{len(calls)}"
                return calls[op]
            if op not in labels:
                labels[op] = f"L{len(labels)}"
            return labels[op]
        # any other bare symbol / literal -> abstract symbol
        return "S"

    toks = []
    for mnem, rest in fn["insns"]:
        ops = [o for o in re.split(r",\s*", rest) if o.strip()] if rest else []
        if mnem in ("lui", "addiu", "ori", "andi", "sltiu", "lw", "sw", "lb", "sb",
                    "lh", "sh", "ld", "sd", "lbu", "lhu", "swc1", "lwc1", "sdc1",
                    "ldc1", "mfc1", "mtc1") and ops:
            # operand 0 may be a register, operand -1 may be an immediate/symbol
            pass
        shown = []
        for i, op in enumerate(ops):
            last = i == len(ops) - 1
            shown.append(norm_operand(op, mnem, last))
        toks.append(f"{mnem}({'|'.join(shown)})")
    return tuple(toks)


def lev(a: tuple, b: tuple) -> int:
    if abs(len(a) - len(b)) > 4:
        return 99
    prev = list(range(len(b) + 1))
    for i, x in enumerate(a, 1):
        cur = [i]
        for j, y in enumerate(b, 1):
            cur.append(min(prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + (x != y)))
        prev = cur
    return prev[-1]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--min-cluster", type=int, default=2)
    ap.add_argument("--max-insns", type=int, default=200)
    ap.add_argument("--json", type=Path, default=None)
    ap.add_argument("--stems", default="")
    ap.add_argument("--clone-dist", type=int, default=0,
                    help="max token edit distance for a matched-clone (0 = exact)")
    ap.add_argument("--mnemonics", action="store_true",
                    help="cluster by mnemonic sequence only (registers/immediates "
                         "abstracted) - finds families with the same shape but "
                         "different constants")
    ap.add_argument("--clone-of", default="",
                    help="comma-separated stems/symbols of *newly matched* "
                         "functions; report the closest unmatched functions to "
                         "each (the sibling-exploitation report)")
    ap.add_argument("--clone-of-file", type=Path, default=None,
                    help="file of stems (one per line) for --clone-of")
    ap.add_argument("--clone-of-dist", type=int, default=6,
                    help="max token edit distance for the --clone-of report")
    ap.add_argument("--clone-of-json", type=Path, default=None)
    args = ap.parse_args()

    mm = matched_map()
    backlog = {p.stem for p in (ROOT / "src" / "non_matching").glob("*.c")}
    fns: dict[str, dict] = {}
    for p in sorted(COD.glob("*.s")):
        fns[p.stem] = parse(p.stem)
    for f in fns.values():
        f["sig"] = normalize(f)
        f["msig"] = tuple(t.split("(")[0] for t in f["sig"])

    sig_key = "msig" if args.mnemonics else "sig"

    remaining = [s for s in fns if s not in mm]
    if args.stems:
        want = {s.strip() for s in args.stems.split(",")}
        remaining = [s for s in remaining if ({s} & want) or
                     ({fns[s]["symbol"]} & want)]
    # classification
    hand = [s for s in remaining if fns[s]["handwritten"]]
    stubs = [s for s in remaining if fns[s]["has_syscall"]]
    real = [s for s in remaining
            if s not in hand and s not in stubs
            and len(fns[s]["insns"]) <= args.max_insns]

    print(f"{len(fns)} functions total; {len(mm)} matched; "
          f"{len(remaining)} remaining")
    print(f"  handwritten markers: {len(hand)}   syscall instr: {len(stubs)}   "
          f"real C pool (<= {args.max_insns} insns): {len(real)}   "
          f"in backlog: {len([s for s in real if s in backlog])}")

    # clusters over the real pool (exclude the already-tracked backlog?)
    clusters: dict[tuple, list[str]] = {}
    for s in real:
        clusters.setdefault(fns[s][sig_key], []).append(s)
    rows = [(len(v), min(len(fns[x]['insns']) for x in v), v[0], v, k)
            for k, v in clusters.items()]
    rows.sort(key=lambda r: (-r[0], r[1]))
    multi = [r for r in rows if r[0] >= args.min_cluster]
    print(f"\n=== clusters (>= {args.min_cluster} members, real pool only) ===")
    print(f"{'size':>4} {'min':>4}  members")
    for n, mn, first, members, sig in multi[:60]:
        head = " ".join(members[:12]) + (" ..." if len(members) > 12 else "")
        print(f"{n:>4} {mn:>4}  {head}")

    # exact clones of matched functions
    matched_sigs: dict[tuple, list[str]] = {}
    for s in mm:
        if s in fns:
            matched_sigs.setdefault(fns[s]["sig"], []).append(s)
    clones = []
    for s in real:
        best_d, best_m = 99, []
        for sig, ms in matched_sigs.items():
            d = lev(fns[s]["sig"], sig)
            if d < best_d:
                best_d, best_m = d, ms
                if d == 0:
                    break
        if best_d <= args.clone_dist:
            clones.append((len(fns[s]["insns"]), best_d, s, best_m[0], mm.get(best_m[0], "")))
    clones.sort()
    print(f"\n=== clones of matched functions (dist <= {args.clone_dist}) ===")
    for n, d, s, m, cc in clones[:80]:
        print(f"  {s} ({n} insn) ~= {m} (cc={cc or 'def'})  dist={d}")
    if not clones:
        print("  (none)")

    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps({
            "matched": len(mm),
            "remaining": len(remaining),
            "handwritten": hand,
            "syscall_stubs": stubs,
            "clusters": [
                {"size": n, "min_insns": mn, "members": m}
                for n, mn, _, m, _ in multi
            ],
            "clones": [
                {"stem": s, "insns": n, "dist": d, "matched": m, "cc": cc}
                for n, d, s, m, cc in clones
            ],
            "real_pool": real,
        }, indent=1), encoding="utf-8")
        print(f"\nwrote {args.json}")

    # --clone-of: the sibling-exploitation report.  For a set of *newly
    # matched* stems, list the unmatched functions closest to each of them by
    # normalized token edit distance.  The closest targets are the cheapest
    # next drafts (copy the matched C and adapt the symbols/constants).
    src_stems: list[str] = []
    if args.clone_of:
        src_stems += [s.strip() for s in args.clone_of.split(",") if s.strip()]
    if args.clone_of_file:
        src_stems += [ln.strip() for ln in
                      args.clone_of_file.read_text().splitlines()
                      if ln.strip() and not ln.startswith("#")]
    if src_stems:
        by_symbol = {fns[s]["symbol"]: s for s in fns if fns[s]["symbol"]}
        src_stems = [by_symbol.get(s, s) for s in src_stems]
        src_stems = [s for s in src_stems if s in fns]
        # match target stems only against unmatched, real functions
        report = []
        for s in src_stems:
            ds = [(lev(fns[t]["sig"], fns[s]["sig"]), t)
                  for t in real if t != s]
            ds = [d for d in ds if d[0] <= args.clone_of_dist]
            ds.sort()
            report.append({"matched": s, "symbol": fns[s]["symbol"],
                           "cc": mm.get(s, ""),
                           "insns": len(fns[s]["insns"]),
                           "targets": [{"stem": t, "dist": d} for d, t in ds[:12]]})
        print(f"\n=== closest unmatched to the newly matched ({len(src_stems)} srcs, "
              f"dist <= {args.clone_of_dist}) ===")
        for row in report:
            if not row["targets"]:
                print(f"  {row['matched']} ({row['insns']} insn, "
                      f"cc={row['cc'] or 'def'}): no close target")
                continue
            head = " ".join(f"{t['stem']}({t['dist']})" for t in row["targets"])
            print(f"  {row['matched']} ({row['insns']} insn, "
                  f"cc={row['cc'] or 'def'}): {head}")
        if args.clone_of_json:
            args.clone_of_json.parent.mkdir(parents=True, exist_ok=True)
            args.clone_of_json.write_text(json.dumps(report, indent=1),
                                          encoding="utf-8")
            print(f"wrote {args.clone_of_json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
