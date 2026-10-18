#!/usr/bin/env python3
"""Statement-order permutation generator (Session 22).

GCC's list scheduler breaks priority ties by source order (INSN_LUID), so for
store-heavy setup code (GS register packets, request records, DMA tags) the
*order of independent statements* decides the emitted order.  Adjacent swaps
(`permute_gen.py swap_stmt`) cannot reach orders that need several moves;
this tool permutes whole runs of consecutive simple statements
(assignments / calls) in the function body, recursing into compound
statements.  Runs with L! <= --limit are enumerated, longer ones sampled.

    python3 tools/permute_stmts.py 0146B8 [--src FILE] [--limit 3000]
    python3 tools/permute_batch.py --stems 0146B8 --cc 29 --only-contains S22_

A byte-exact result is its own proof of equivalence, so the generator does
not check data dependencies.
"""
from __future__ import annotations

import argparse
import itertools
import math
import random
import re
from pathlib import Path

import permute_gen as G

ROOT = Path(__file__).resolve().parent.parent
VARIANTS = ROOT / "build" / "permute"

NOT_SIMPLE = re.compile(
    r"^(if|for|while|do|switch|return|goto|break|continue|case|default|else|"
    r"__asm__|asm|"
    r"(const\s+|volatile\s+|unsigned\s+|signed\s+|static\s+|register\s+)*"
    r"(int|char|short|long|void|float|double|struct|union|enum|u_\w+|[A-Z]\w*_t)\b)")


def simple(stmt: str) -> bool:
    s = stmt.strip()
    if not s.endswith(";") or NOT_SIMPLE.match(s) or re.match(r"^\w+\s*:", s):
        return False
    # a typedef'd declaration such as `sceGsTexEnv *tp = ...;`
    if re.match(r"^[A-Za-z_]\w*\s+\**\s*[A-Za-z_]\w*\s*(=|;|\[)", s):
        return False
    return True


def runs_in(body: str, base: int):
    """[[(abs_start, abs_end), ...]] runs of >= 2 simple statements,
    recursing into `{...}` blocks."""
    out = []
    cur = []
    for s, e in G.find_statements(body):
        txt = body[s:e]
        if simple(txt):
            cur.append((base + s, base + e))
            continue
        if len(cur) >= 2:
            out.append(cur)
        cur = []
        depth = 0
        open_k = 0
        for k, c in enumerate(txt):
            if c == "{":
                if depth == 0:
                    open_k = k
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    out.extend(runs_in(txt[open_k + 1:k], base + s + open_k + 1))
    if len(cur) >= 2:
        out.append(cur)
    return out


def gen(stem: str, src: Path, limit: int, prefix: str, seed: int) -> int:
    text = src.read_text(encoding="utf-8")
    parts = G.split_body(text)
    if not parts:
        return 0
    head, body, _tail = parts
    base = len(head)
    runs = runs_in(body, base)
    if not runs:
        return 0
    rng = random.Random(seed)
    per_run = []
    for r in runs:
        stmts = [text[s:e] for s, e in r]
        n = len(stmts)
        if math.factorial(n) <= limit:
            perms = list(itertools.permutations(range(n)))
        else:
            seen = {tuple(range(n))}
            perms = [tuple(range(n))]
            while len(perms) < limit:
                p = list(range(n))
                rng.shuffle(p)
                if tuple(p) not in seen:
                    seen.add(tuple(p))
                    perms.append(tuple(p))
        per_run.append((r, stmts, perms))
    total = math.prod(len(p[2]) for p in per_run)
    combos = []
    if total <= limit:
        combos = list(itertools.product(*[range(len(p[2])) for p in per_run]))
    else:
        combos = [tuple(0 for _ in per_run)]
        seen = set(combos)
        while len(combos) < limit:
            c = tuple(rng.randrange(len(p[2])) for p in per_run)
            if c not in seen:
                seen.add(c)
                combos.append(c)
    vdir = VARIANTS / stem
    vdir.mkdir(parents=True, exist_ok=True)
    for p in vdir.glob(f"{prefix}*.c"):
        p.unlink()
    n = 0
    for combo in combos:
        edits = []
        for (r, stmts, perms), ci in zip(per_run, combo):
            perm = perms[ci]
            for (s, e), j in zip(r, perm):
                edits.append((s, e, stmts[j]))
        out = text
        for s, e, new in sorted(edits, reverse=True):
            out = out[:s] + new + out[e:]
        (vdir / f"{prefix}{n:05d}.c").write_text(out, encoding="utf-8")
        n += 1
    return n


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--src", type=Path, default=None,
                    help="draft to permute (default src/non_matching/<stem>.c)")
    ap.add_argument("--limit", type=int, default=2000)
    ap.add_argument("--prefix", default="S22_")
    ap.add_argument("--seed", type=int, default=22)
    args = ap.parse_args()
    stems = args.stems
    if args.all:
        stems = sorted(p.stem for p in (ROOT / "src" / "non_matching").glob("*.c"))
    for s in stems:
        src = args.src or ROOT / "src" / "non_matching" / f"{s}.c"
        print(f"{s}: {gen(s, src, args.limit, args.prefix, args.seed)} variants")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
