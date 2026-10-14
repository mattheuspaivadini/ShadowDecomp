#!/usr/bin/env python3
"""Mechanical source-mutation generator for `tools/permute.py` (Session 6).

Takes the baseline C of a function and writes text-level variants implementing
the winning patterns recorded in `docs/non-matching-12.md` plus the families the
Session-5 backlog named (argument evaluation order, constant materialisation
order, loop rotation of table scans).

    python3 tools/permute_gen.py 020D10              # variants -> build/permute/020D10/
    python3 tools/permute_gen.py 020D10 --pairs      # + 2-mutation combinations
    python3 tools/permute_gen.py --all --pairs       # every src/non_matching stem

Design notes
------------
* The mutations are *text* mutations on a tiny statement/expression model (no
  full C parser): a brace/paren-aware scanner finds top-level statements, calls
  and binary chains. This is deliberately coarse - an invalid variant simply
  fails to compile and scores as such, which the permuter already reports.
* Every variant is a complete C file: the baseline text with one (or two)
  mutations applied. The file keeps the original `/* ... */` header comment.
* Names are `v01_<kind>_<n>` so a winning variant can be promoted directly.

Kinds (all derived from evidence in docs/non-matching-12.md / docs/progress.md):

  swap_stmt        adjacent statement order            (store order, #4)
  arg_order        rotate/swap call arguments          (argument order family)
  local_hoist      hoist a call argument into a local  (evaluation order)
  type_unsigned    `int` -> `unsigned int`             (srl, #8)
  paren_assoc      A + B + C  ->  A + (B + C)          (#5/#6)
  loop_form        for <-> while <-> do-while          (#11, table scans)
  index_twice      hoist base pointer -> index twice   (#9/#10/#12)
  addr_cast        (char*)p + n  <->  (int)p + n       (signed slt, #8)
  plus_assign      p += n  <->  p = p + n              (two-step address, #2)
  deref_form       p[0] <-> *p, p->f <-> (*p).f
  decl_split       `int x = a;` <-> `int x; x = a;`    (#8)
  const_local      literal -> named local              (materialisation order)
  negate_test      if (c) A else B -> if (!c) B else A (#10)
  early_return     trailing `if (c) { X; }` -> `if (!c) goto end; X; end:`
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VARIANTS = ROOT / "build" / "permute"


# --------------------------------------------------------------------------
# tiny scanner helpers
# --------------------------------------------------------------------------
def find_statements(body: str):
    """Spans of top-level statements in a function body (between outer braces).

    Returns a list of (start, end) into `body`; `end` is exclusive and includes
    the terminating `;` or the closing `}` of a compound statement.
    """
    spans = []
    i, n = 0, len(body)
    depth_p = depth_b = 0
    start = None
    while i < n:
        c = body[i]
        if start is None and not c.isspace():
            start = i
        if c in "([":
            depth_p += 1
        elif c in ")]":
            depth_p -= 1
        elif c == "{":
            # a brace that starts a *block* (not an initializer)
            prev = body[:i].rstrip()[-1:] if body[:i].rstrip() else ""
            if depth_p == 0 and depth_b == 0 and prev not in "=,( ":
                depth_b += 1
            elif depth_b:
                depth_b += 1
        elif c == "}":
            depth_b -= 1
            if depth_b == 0 and depth_p == 0:
                spans.append((start, i + 1))
                start = None
        elif c == ";" and depth_p == 0 and depth_b == 0:
            spans.append((start, i + 1))
            start = None
        i += 1
    return spans


def split_body(text: str):
    """(header, body, tail) around the outermost function body braces."""
    m = re.search(r"\{", text)
    if not m:
        return None
    start = m.start()
    depth = 0
    for i in range(start, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return text[:start + 1], text[start + 1:i], text[i:]
    return None


def balanced(text: str) -> bool:
    pairs = {"(": ")", "[": "]", "{": "}"}
    stack = []
    i = 0
    while i < len(text):
        c = text[i]
        if c == "/" and text[i:i + 2] == "/*":
            j = text.find("*/", i + 2)
            i = len(text) if j < 0 else j + 2
            continue
        if c == "/" and text[i:i + 2] == "//":
            j = text.find("\n", i)
            i = len(text) if j < 0 else j + 1
            continue
        if c in pairs:
            stack.append(pairs[c])
        elif c in ")]}":
            if not stack or stack.pop() != c:
                return False
        i += 1
    return not stack


def code_part(text: str) -> str:
    """The text with comments blanked (offsets preserved)."""
    out = list(text)
    i = 0
    while i < len(text):
        if text[i:i + 2] == "/*":
            j = text.find("*/", i + 2)
            j = len(text) if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif text[i:i + 2] == "//":
            j = text.find("\n", i)
            j = len(text) if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        else:
            i += 1
    return "".join(out)


# --------------------------------------------------------------------------
# mutations: each returns a list of (name, new_text)
# --------------------------------------------------------------------------
def mut_swap_stmt(text):
    out = []
    sb = split_body(text)
    if not sb:
        return out
    head, body, tail = sb
    code = code_part(body)
    spans = find_statements(code)
    for k in range(len(spans) - 1):
        a0, a1 = spans[k]
        b0, b1 = spans[k + 1]
        sa, sb_ = body[a0:a1], body[b0:b1]
        if re.search(r"\b(return|break|continue|goto|else)\b", sa + sb_):
            continue
        if not sa.strip() or not sb_.strip():
            continue
        # keep declarations before code (C89): only swap if the same class
        da = bool(re.match(r"\s*(struct|union|enum|unsigned|signed|char|short|int|long|float|double|void|const|volatile|static)\b", sa))
        db = bool(re.match(r"\s*(struct|union|enum|unsigned|signed|char|short|int|long|float|double|void|const|volatile|static)\b", sb_))
        if da != db:
            continue
        new = body[:a0] + sb_ + body[a1:b0] + sa + body[b1:]
        out.append((f"swap_stmt_{k}", head + new + tail))
    return out


CALL_RE = re.compile(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(")


def _find_calls(code: str):
    """(name, open_idx, close_idx) for each call whose args are balanced."""
    out = []
    for m in CALL_RE.finditer(code):
        if m.group(1) in ("if", "for", "while", "switch", "return", "sizeof"):
            continue
        i = m.end() - 1
        depth = 0
        for j in range(i, len(code)):
            if code[j] == "(":
                depth += 1
            elif code[j] == ")":
                depth -= 1
                if depth == 0:
                    args = code[i + 1:j]
                    out.append((m.group(1), i + 1, j, args))
                    break
    return out


def _split_args(args: str):
    parts, depth, cur, start = [], 0, [], 0
    for k, c in enumerate(args):
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == "," and depth == 0:
            parts.append(args[start:k])
            start = k + 1
    parts.append(args[start:])
    return parts


def mut_arg_order(text):
    out = []
    sb = split_body(text)
    if not sb:
        return out
    head, body, tail = sb
    code = code_part(body)
    seen = 0
    for name, a0, a1, args in _find_calls(code):
        parts = _split_args(args)
        if len(parts) < 2 or any("(" in p and ")" in p and "," in p for p in parts):
            pass
        if len(parts) < 2:
            continue
        if not all(re.fullmatch(r"\s*[^,;{}]*\s*", p) for p in parts):
            continue
        for label, perm in (("rot1", parts[1:] + parts[:1]),
                            ("rot2", parts[-1:] + parts[:-1]),
                            ("swap12", [parts[1], parts[0]] + parts[2:]),
                            ("swap_last", parts[:-2] + [parts[-1], parts[-2]] if len(parts) >= 2 else parts)):
            if perm == parts:
                continue
            new_args = ",".join(perm)
            new = body[:a0] + new_args + body[a1:]
            out.append((f"arg_order_{name}_{label}_{seen}", head + new + tail))
            seen += 1
    return out


def mut_local_hoist(text):
    """`f(g(), x)` -> `t = g(); f(t, x);` for a call argument that is itself a
    call (evaluation order is what the family is about)."""
    out = []
    sb = split_body(text)
    if not sb:
        return out
    head, body, tail = sb
    code = code_part(body)
    seen = 0
    for name, a0, a1, args in _find_calls(code):
        parts = _split_args(args)
        for k, p in enumerate(parts):
            if not re.fullmatch(r"\s*[A-Za-z_][A-Za-z0-9_]*\s*\([^()]*\)\s*", p):
                continue
            stmt_start = body.rfind(";", 0, a0) + 1
            stmt_start = body.rfind("{", 0, a0) + 1 if body.rfind("{", 0, a0) > stmt_start else stmt_start
            indent = re.match(r"\s*", body[stmt_start:]).group(0)
            parts2 = list(parts)
            parts2[k] = " hoisted"
            new_args = ",".join(parts2)
            new = (body[:stmt_start] + indent + f"int hoisted = {p.strip()};\n" + indent
                   + body[stmt_start:a0] + new_args + body[a1:])
            out.append((f"local_hoist_{name}_{k}_{seen}", head + new + tail))
            seen += 1
    return out


def mut_type_unsigned(text):
    out = []
    code = code_part(text)
    # local declarations `int x` / `int *p`
    for m in list(re.finditer(r"\bint\s+([A-Za-z_][A-Za-z0-9_]*)", code)):
        i = m.start()
        if code[max(0, i - 8):i].rstrip().endswith("unsigned"):
            continue
        new = text[:i] + "unsigned int" + text[m.end(0) - len(m.group(0)) + len("int"):]
        out.append((f"type_unsigned_{m.group(1)}_{i}", new))
    # struct fields
    for m in list(re.finditer(r"^\s*int\s+([A-Za-z_][A-Za-z0-9_]*)\s*;", text, re.M)):
        i = m.start()
        new = text[:i] + m.group(0).replace("int", "unsigned int", 1) + text[m.end():]
        out.append((f"type_unsigned_field_{m.group(1)}_{i}", new))
    return out[:12]


def mut_paren_assoc(text):
    out = []
    code = code_part(text)
    seen = 0
    for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*\s*(?:->|\.)[A-Za-z_][A-Za-z0-9_]*)\s*\+\s*([A-Za-z0-9_]+)\s*\+\s*([A-Za-z0-9_]+)", code):
        a, b, c = m.group(1), m.group(2), m.group(3)
        new = text[:m.start()] + f"{a} + ({b} + {c})" + text[m.end():]
        out.append((f"paren_assoc_{seen}", new))
        seen += 1
    for m in re.finditer(r"\(([A-Za-z_][A-Za-z0-9_]*)\s*\+\s*([A-Za-z0-9_]+)\)\s*\+\s*([A-Za-z0-9_]+)", code):
        a, b, c = m.group(1), m.group(2), m.group(3)
        new = text[:m.start()] + f"{a} + ({b} + {c})" + text[m.end():]
        out.append((f"paren_assoc_chain_{seen}", new))
        seen += 1
    return out


def mut_loop_form(text):
    out = []
    code = code_part(text)
    for m in list(re.finditer(
            r"for\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*([^;]+);\s*\1\s*<\s*([^;]+);\s*\1\s*\+\+\s*\)", code)):
        var, lo, hi = m.group(1), m.group(2), m.group(3)
        # find the body braces
        j = code.find("{", m.end())
        if j < 0:
            continue
        depth = 0
        for k in range(j, len(code)):
            if code[k] == "{":
                depth += 1
            elif code[k] == "}":
                depth -= 1
                if depth == 0:
                    inner = text[j + 1:k]
                    head = text[:m.start()]
                    tail = text[k + 1:]
                    out.append((f"loop_while_{var}",
                                head + f"{var} = {lo};\nwhile ({var} < {hi}) {{\n{inner}\n{var}++;\n}}" + tail))
                    out.append((f"loop_do_{var}",
                                head + f"{var} = {lo};\ndo {{\n{inner}\n{var}++;\n}} while ({var} < {hi});" + tail))
                    break
        if len(out) >= 6:
            break
    return out


def mut_index_twice(text):
    """hoist `T[i]` used several times into a local, and vice versa."""
    out = []
    sb = split_body(text)
    if not sb:
        return out
    head, body, tail = sb
    code = code_part(body)
    seen = 0
    for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*(?:\s*->\s*[A-Za-z_][A-Za-z0-9_]*)?\[[^\[\]]+\])", code):
        expr = m.group(1)
        if expr.count("[") != 1:
            continue
        if code.count(expr) < 2:
            continue
        # introduce a local pointer at the top of the body
        new = body[:0] + f"char *idx_base = (char *)&({expr});\n" + body
        out.append((f"index_base_{seen}", head + new + tail))
        seen += 1
        if seen >= 4:
            break
    return out


def mut_addr_cast(text):
    out = []
    for m in re.finditer(r"\(char\s*\*\)\s*([A-Za-z_][A-Za-z0-9_]*)", text):
        new = text[:m.start()] + f"(int){m.group(1)}" + text[m.end():]
        out.append((f"addr_cast_int_{m.group(1)}_{m.start()}", new))
    for m in re.finditer(r"\(int\)\s*([A-Za-z_][A-Za-z0-9_]*)", text):
        new = text[:m.start()] + f"(char *){m.group(1)}" + text[m.end():]
        out.append((f"addr_cast_char_{m.group(1)}_{m.start()}", new))
    return out[:8]


def mut_plus_assign(text):
    out = []
    for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*)\s*\+=\s*([^;]+);", text):
        var, val = m.group(1), m.group(2)
        new = text[:m.start()] + f"{var} = {var} + {val};" + text[m.end():]
        out.append((f"plus_assign_split_{var}_{m.start()}", new))
    for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*)\s*=\s*\1\s*\+\s*([^;]+);", text):
        var, val = m.group(1), m.group(2)
        new = text[:m.start()] + f"{var} += {val};" + text[m.end():]
        out.append((f"plus_assign_join_{var}_{m.start()}", new))
    return out[:8]


def mut_decl_split(text):
    out = []
    sb = split_body(text)
    if not sb:
        return out
    head, body, tail = sb
    code = code_part(body)
    for m in re.finditer(r"\b(unsigned\s+int|int|long long|unsigned)\s+([A-Za-z_][A-Za-z0-9_]*)\s*=\s*([^;]+);", code):
        typ, var, val = m.group(1), m.group(2), m.group(3)
        new = body[:m.start()] + f"{typ} {var};\n{var} = {val};" + body[m.end():]
        out.append((f"decl_split_{var}", head + new + tail))
    return out[:8]


def mut_const_local(text):
    """literal in an expression -> named local (materialisation order)."""
    out = []
    sb = split_body(text)
    if not sb:
        return out
    head, body, tail = sb
    code = code_part(body)
    seen = 0
    for m in re.finditer(r"(?<![\w.])(0x[0-9A-Fa-f]+|\d+)(?![\w.])", code):
        lit = m.group(1)
        if lit in ("0", "1"):
            continue
        if m.start() < code.find("{") + 1:
            continue
        new = body[:0] + f"int lit_{seen} = {lit};\n" + body[:m.start()] + f"lit_{seen}" + body[m.end():]
        out.append((f"const_local_{lit}_{seen}", head + new + tail))
        seen += 1
        if seen >= 4:
            break
    return out


def mut_negate_test(text):
    out = []
    for m in re.finditer(r"if\s*\(([^()]+)\)\s*\{([^{}]*)\}\s*else\s*\{([^{}]*)\}", text):
        cond, a, b = m.group(1).strip(), m.group(2), m.group(3)
        new = text[:m.start()] + f"if (!({cond})) {{{b}}} else {{{a}}}" + text[m.end():]
        out.append((f"negate_test_{m.start()}", new))
    return out[:6]


def mut_early_return(text):
    out = []
    sb = split_body(text)
    if not sb:
        return out
    head, body, tail = sb
    code = code_part(body)
    spans = find_statements(code)
    if len(spans) >= 1:
        a0, a1 = spans[-1]
        stmt = body[a0:a1]
        m = re.match(r"\s*if\s*\(([^()]*)\)\s*\{", stmt)
        if m and stmt.rstrip().endswith("}"):
            cond = m.group(1)
            inner = stmt[m.end():stmt.rstrip().rfind("}")]
            new = (body[:a0] + f"if (!({cond})) goto done;\n" + inner + "\ndone:;\n" + body[a1:])
            out.append(("early_return_goto", head + new + tail))
    return out


MUTATIONS = [
    mut_swap_stmt, mut_arg_order, mut_local_hoist, mut_type_unsigned,
    mut_paren_assoc, mut_loop_form, mut_index_twice, mut_addr_cast,
    mut_plus_assign, mut_decl_split, mut_const_local, mut_negate_test,
    mut_early_return,
]


def variants_for(text: str, with_pairs: bool, limit: int):
    """{name: text} - single mutations plus (optionally) pairs."""
    out: dict[str, str] = {}
    singles = []
    for fn in MUTATIONS:
        try:
            got = fn(text)
        except Exception:  # a coarse text mutation can always trip on odd input
            got = []
        for name, new in got:
            if new == text or not balanced(new):
                continue
            key = f"v{len(out) + 1:02d}_{name}"
            if key not in out:
                out[key] = new
                singles.append((key, new))
            if len(out) >= limit:
                return out
    if with_pairs:
        base_names = list(singles)
        for key, new in base_names:
            for fn in MUTATIONS:
                try:
                    got = fn(new)
                except Exception:
                    got = []
                for name, new2 in got:
                    if new2 == new or not balanced(new2):
                        continue
                    if len(out) >= limit:
                        return out
                    k = f"v{len(out) + 1:02d}_x_{key}_{name}"
                    out[k] = new2
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--all", action="store_true", help="every src/non_matching/*.c")
    ap.add_argument("--pairs", action="store_true", help="also 2-mutation combinations")
    ap.add_argument("--limit", type=int, default=400)
    ap.add_argument("--clean", action="store_true", help="remove old generated variants first")
    args = ap.parse_args()

    stems = args.stems
    if args.all or not stems:
        stems = sorted(p.stem for p in (ROOT / "src" / "non_matching").glob("*.c"))
    total = 0
    for stem in stems:
        src = ROOT / "src" / "non_matching" / f"{stem}.c"
        if not src.exists():
            src = ROOT / "src" / "cod" / f"{stem}.c"
        if not src.exists():
            print(f"  {stem}: no source")
            continue
        vdir = VARIANTS / stem
        vdir.mkdir(parents=True, exist_ok=True)
        if args.clean:
            for p in vdir.glob("v*.c"):
                p.unlink()
        base = vdir / "v00_baseline.c"
        if not base.exists():
            base.write_text(src.read_text(encoding="utf-8"), encoding="utf-8")
        text = base.read_text(encoding="utf-8")
        variants = variants_for(text, args.pairs, args.limit)
        for name, new in variants.items():
            (vdir / f"{name}.c").write_text(new, encoding="utf-8")
        print(f"  {stem}: {len(variants)} variants")
        total += len(variants)
    print(f"{total} variants generated")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
