#!/usr/bin/env python3
"""Type-mutation generator for the permuter (Session 22).

EE-GCC's scheduler only reorders a load across a store when type-based alias
analysis (TBAA) proves they cannot overlap, so the *declared type* of a struct
field or global decides which loads may float above which stores.  Session 22
found that many "scheduler-only" residuals vanish once a field that holds a
pointer is declared `void *` (or a counter `unsigned int`).  This tool writes
one variant per type change (and optionally per pair of changes) into
build/permute/<stem>/<prefix>NNN_<desc>.c for `tools/permute_batch.py`.

    python3 tools/permute_types.py 0098F0 015E40 [--pairs] [--limit 300]
    python3 tools/permute_types.py --all --clean
"""
from __future__ import annotations

import argparse
import itertools
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VARIANTS = ROOT / "build" / "permute"

# scalar spelling -> alternative spellings that keep the size
ALTS = {
    "int": ["void *", "unsigned int"],
    "unsigned int": ["void *", "int"],
    "unsigned": ["void *", "int"],
    "short": ["unsigned short"],
    "unsigned short": ["short"],
    "char": ["unsigned char"],
    "unsigned char": ["char"],
    "void *": ["int", "char *"],
    "char *": ["void *"],
}
SCALAR = r"(unsigned\s+int|unsigned\s+short|unsigned\s+char|unsigned|int|short|char)"

MEMBER_RE = re.compile(
    rf"^(?P<ind>[ \t]+)(?P<ty>{SCALAR}|void\s*\*|char\s*\*)\s*(?P<star>\*?)\s*(?P<name>[A-Za-z_]\w*)\s*;",
    re.M)
EXTERN_RE = re.compile(
    rf"^extern\s+(?P<ty>{SCALAR}|void\s*\*)\s+(?P<name>D_[0-9A-Fa-f]{{8}}|[A-Za-z_]\w*)\s*(?P<arr>\[\d*\])?\s*;",
    re.M)


def norm(t: str) -> str:
    t = re.sub(r"\s+", " ", t.strip())
    return t.replace(" *", " *").replace("void*", "void *").replace("char*", "char *")


def struct_spans(text: str):
    """(start, end) of every `struct ... { ... }` body (non-nested)."""
    for m in re.finditer(r"\b(struct|union)\s*\w*\s*\{", text):
        i = m.end()
        depth = 1
        while i < len(text) and depth:
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
            i += 1
        yield m.end(), i


LOCAL_RE = re.compile(
    rf"^(?P<ind>[ \t]+)(?P<ty>{SCALAR}|void\s*\*|char\s*\*)\s*(?P<star>\*?)\s*(?P<name>[A-Za-z_]\w*)\s*(=[^;]*)?;",
    re.M)
PARAM_RE = re.compile(
    rf"(?P<ty>{SCALAR}|void\s*\*|char\s*\*)\s*(?P<star>\*?)\s*(?P<name>[A-Za-z_]\w*)\s*(?=[,)])")
FUNC_RE = re.compile(r"^[A-Za-z_][^;{}\n]*\((?P<params>[^)]*)\)\s*\{", re.M)


def expand_one_line_structs(text: str) -> str:
    """Put each member of a one-line `struct X { a; b; };` on its own line."""
    def rep(m):
        members = [x.strip() for x in m.group(2).split(";") if x.strip()]
        return m.group(1) + "{\n" + "".join(f"    {x};\n" for x in members) + "}"
    return re.sub(r"^((?:typedef\s+)?(?:struct|union)\s*\w*\s*)\{([^{}\n]*;[^{}\n]*)\}", rep,
                  text, flags=re.M)


def sites(text: str, locals_: bool = False):
    """List of (start, end, old_type, name, kind)."""
    out = []
    spans = list(struct_spans(text))
    for a, b in spans:
        for m in MEMBER_RE.finditer(text, a, b):
            if m.end() > b:
                break
            ty = norm(m.group("ty") + (" *" if m.group("star") else ""))
            if ty in ALTS:
                out.append((m.start("ty"), m.end("star") if m.group("star") else m.end("ty"),
                            ty, m.group("name"), "m"))
    for m in EXTERN_RE.finditer(text):
        ty = norm(m.group("ty"))
        if ty in ALTS:
            out.append((m.start("ty"), m.end("ty"), ty, m.group("name"), "g"))
    if locals_:
        # function-body locals and the parameters of each definition
        for m in LOCAL_RE.finditer(text):
            if any(a <= m.start() < b for a, b in spans):
                continue
            ty = norm(m.group("ty") + (" *" if m.group("star") else ""))
            if ty in ALTS:
                out.append((m.start("ty"), m.end("star") if m.group("star") else m.end("ty"),
                            ty, m.group("name"), "l"))
        for f in FUNC_RE.finditer(text):
            base = f.start("params")
            for m in PARAM_RE.finditer(f.group("params")):
                ty = norm(m.group("ty") + (" *" if m.group("star") else ""))
                if ty in ALTS:
                    end = m.end("star") if m.group("star") else m.end("ty")
                    out.append((base + m.start("ty"), base + end, ty, m.group("name"), "p"))
    return out


def apply(text: str, changes):
    for s, e, new in sorted(changes, reverse=True):
        text = text[:s] + new + text[e:]
    return text


def gen(stem: str, pairs: bool, limit: int, prefix: str, clean: bool,
        src: Path | None = None, out: Path | None = None, locals_: bool = False) -> int:
    src = src or ROOT / "src" / "non_matching" / f"{stem}.c"
    if not src.exists():
        return 0
    text = expand_one_line_structs(src.read_text(encoding="utf-8"))
    vdir = out or VARIANTS / stem
    vdir.mkdir(parents=True, exist_ok=True)
    if clean:
        for p in vdir.glob(f"{prefix}*.c"):
            p.unlink()
    ss = sites(text, locals_)
    singles = []
    for s, e, ty, name, kind in ss:
        for alt in ALTS[ty]:
            singles.append(((s, e, alt), f"{name}_{re.sub(r'[^a-z]', '', alt)}"))
    combos = [(c,) for c in singles]
    if pairs:
        for x, y in itertools.combinations(singles, 2):
            if x[0][0] != y[0][0]:
                combos.append((x, y))
    n = 0
    for combo in combos[:limit]:
        body = apply(text, [c[0] for c in combo])
        desc = "+".join(c[1] for c in combo)[:60]
        (vdir / f"{prefix}{n:03d}_{desc}.c").write_text(body, encoding="utf-8")
        n += 1
    (vdir / "v00_baseline.c").write_text(text, encoding="utf-8")
    return n


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--pairs", action="store_true")
    ap.add_argument("--limit", type=int, default=400)
    ap.add_argument("--prefix", default="T22_")
    ap.add_argument("--clean", action="store_true")
    ap.add_argument("--src", type=Path, default=None, help="draft to mutate")
    ap.add_argument("--out", type=Path, default=None, help="variant directory")
    ap.add_argument("--locals", action="store_true",
                    help="also mutate function locals and parameters (register-role residuals)")
    args = ap.parse_args()
    stems = args.stems
    if args.all:
        stems = sorted(p.stem for p in (ROOT / "src" / "non_matching").glob("*.c"))
    for s in stems:
        print(f"{s}: {gen(s, args.pairs, args.limit, args.prefix, args.clean, args.src, args.out, args.locals)} variants")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
