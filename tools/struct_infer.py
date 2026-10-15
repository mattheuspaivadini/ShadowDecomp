#!/usr/bin/env python3
"""Infer struct layouts from base-register + offset access patterns (Phase D).

For a function, follow the load/store instructions and group them by their base
register. A base that is loaded once from a global and then accessed at several
fixed offsets is a struct pointer; the offsets are the fields. Confidence is the
number of distinct offsets seen for that base (a base with >= 3 offsets is a
likely struct; 1-2 offsets may be a scalar array or a stack slot).

Output is a paste-ready C skeleton:

    struct S_<stem>_<base> {
        char pad00[0x08];
        int  f08;          /* 0x08 */
        ...
    };

    python3 tools/struct_infer.py 016298
    python3 tools/struct_infer.py --top 20          # most promising stems
"""
from __future__ import annotations

import argparse
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COD = ROOT / "asm" / "cod"

LINE = re.compile(
    r"^\s*/\*.*?\*/\s*(\S+)\s+(.*?)\s*$")
MEM = re.compile(r"^(-?(?:0x[0-9A-Fa-f]+|\d+))\((\$[a-z0-9]+)\)$")

# base registers worth modelling (callee-saved + the globals-pointer)
BASES = {"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
         "$fp", "$a0", "$a1", "$a2", "$a3", "$v0", "$v1"}

SIZES = {"lw": 4, "sw": 4, "lb": 1, "lbu": 1, "sb": 1, "lh": 2, "lhu": 2,
         "sh": 2, "ld": 8, "sd": 8, "lwc1": 4, "swc1": 4, "ldc1": 8,
         "sdc1": 8, "lq": 16, "sq": 16, "lwl": 4, "lwr": 4, "swl": 4,
         "swr": 4, "ldl": 8, "ldr": 8, "sdl": 8, "sdr": 8}


def accesses(stem: str) -> dict[str, dict[int, set[str]]]:
    p = COD / f"{stem}.s"
    if not p.exists():
        return {}
    out: dict[str, dict[int, set[str]]] = defaultdict(lambda: defaultdict(set))
    for raw in p.read_text(encoding="utf-8", errors="replace").splitlines():
        m = LINE.match(raw)
        if not m:
            continue
        mnem, rest = m.group(1), m.group(2)
        if mnem not in SIZES:
            continue
        ops = [o.strip() for o in rest.split(",")]
        if not ops:
            continue
        mo = MEM.match(ops[-1])
        if not mo:
            continue
        off = int(mo.group(1), 0)
        base = mo.group(2)
        if base not in BASES or off < 0:
            continue
        out[base][off].add(mnem)
    return out


def emit(stem: str, base: str, fields: dict[int, set[str]]) -> str:
    lines = [f"/* {stem}: {base} - {len(fields)} distinct offsets */",
             f"struct S_{stem}_{base.strip('$')} {{"]
    offs = sorted(fields)
    cur = 0
    for off in offs:
        if off > cur:
            lines.append(f"    char pad{cur:02X}[0x{off - cur:X}];")
        sz = max(SIZES[m] for m in fields[off])
        ctype = {1: "unsigned char", 2: "unsigned short",
                 4: "int", 8: "long long", 16: "char"}[sz]
        name = f"f{off:02X}"
        suffix = "[16]" if sz == 16 else ""
        lines.append(f"    {ctype:<15} {name}{suffix};  /* 0x{off:02X} "
                     f"{'/'.join(sorted(fields[off]))} */")
        cur = off + sz
    lines.append("};")
    return "\n".join(lines)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--top", type=int, default=0,
                    help="rank the untouched pool by field count instead")
    ap.add_argument("--min-fields", type=int, default=3)
    args = ap.parse_args()

    if args.top:
        import json
        led = json.loads((ROOT / "docs" / "ledger.json").read_text())
        scored = []
        for stem, r in led["functions"].items():
            if r["status"] != "untouched":
                continue
            acc = accesses(stem)
            best = max((len(f) for f in acc.values()), default=0)
            scored.append((best, r["insns"], stem))
        scored.sort(key=lambda x: (-x[0], x[1]))
        print(f"{'fields':>6} {'insns':>5}  stem")
        for n, ins, stem in scored[:args.top]:
            print(f"{n:>6} {ins:>5}  {stem}")
        return 0

    for stem in args.stems:
        acc = accesses(stem)
        shown = 0
        for base, fields in sorted(acc.items(),
                                   key=lambda kv: -len(kv[1])):
            if len(fields) < args.min_fields:
                continue
            print(emit(stem, base, fields))
            print()
            shown += 1
        if not shown:
            print(f"/* {stem}: no base with >= {args.min_fields} offsets */")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
