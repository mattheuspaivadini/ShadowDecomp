#!/usr/bin/env python3
"""Draft generator for .XFF leaf functions whose whole body is one inline-asm block.

The VU0 macro-mode / MMI helpers in the overlays (`iosInitCurrentMatrix`,
`iosApplyCurrentMatrix`, ...) are leaf routines written as
`__asm__ __volatile__("...")` in C: the body has no frame, no call, no branch,
and ends with `jr $ra` + a `nop` delay slot (GCC never moves a volatile asm into
a delay slot, which is the tell). This emits that C for every such function so
`tools/xff_try.py` can prove it byte-exact; nothing is accepted without the diff.

Usage:
    python tools/xff_asmbody.py KERNEL OUTDIR [--stems 00bc68 ...]
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import xfflib  # noqa: E402
from xff_dis import decode  # noqa: E402

BRANCHY = re.compile(r"^(b|j|jal|jalr|jr|syscall|break|eret)\b|^b\w*\b")
AREGS = ["$a0", "$a1", "$a2", "$a3"]
FREGS = ["$f12", "$f13", "$f14", "$f15"]
GPRS = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 "
        "t8 t9 k0 k1 gp sp fp ra").split()


def gas(ins: str) -> str:
    """rabbitizer spelling -> what the EE-GCC 2.9x gas accepts (numeric GPRs, bare ACC/Q/I/R/P)."""
    ins = " ".join(ins.split())
    ins = re.sub(r"\$(ACC|Q|I|R|P)\b", r"\1", ins)
    return re.sub(r"\$([a-z]+[0-9]?)\b",
                  lambda m: f"${GPRS.index(m.group(1))}" if m.group(1) in GPRS else m.group(0), ins)


def draft(mod: dict, start: int, end: int, name: str) -> str | None:
    words = [int.from_bytes(mod["text"][pc:pc + 4], "little") for pc in range(start, end, 4)]
    if len(words) < 3 or words[-2] != 0x03E00008 or words[-1] != 0:
        return None
    if any(start <= r["offset"] < end for r in mod["relocs"]):
        return None
    body = [decode(w, start + 4 * i) for i, w in enumerate(words[:-2])]
    for ins in body:
        op = ins.split()[0]
        if ins.startswith(".word") or BRANCHY.match(op) or "$sp" in ins or "$ra" in ins:
            return None
    text = " ".join(body)
    # plain-CPU bodies (volatile MMIO stores, float returns) are compiled C, not asm
    if not re.search(r"\$vf|\$vi|\blq|\bsq|\bqm|\bc[ft]c2|\bp[a-z]+\b", text):
        return None
    nint = max([i + 1 for i, r in enumerate(AREGS) if r in text] or [0])
    nflt = max([i + 1 for i, r in enumerate(FREGS) if r in text] or [0])
    params = [f"void *a{i}" for i in range(nint)] + [f"float f{12 + i}" for i in range(nflt)]
    ret = "int" if re.search(r"\$v[01]\b", text) else "void"
    lines = "\n".join(f'        "{gas(ins)}\\n"' for ins in body)
    head = (f"/* KERNEL.XFF @ 0x{start:06X} ({end - start} B) - {name}\n"
            f" * Evidence: leaf with no frame, call or branch; the body is one volatile\n"
            f" * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a\n"
            f" * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the\n"
            f" * argument registers directly).\n */\n")
    return (f"{head}{ret} {name}({', '.join(params) or 'void'}) {{\n"
            f"    __asm__ __volatile__(\n{lines});\n}}\n")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("outdir")
    ap.add_argument("--stems", nargs="*")
    args = ap.parse_args()
    mod = xfflib.load_module(args.module)
    out = Path(args.outdir)
    out.mkdir(parents=True, exist_ok=True)
    want = {s.lower() for s in args.stems} if args.stems else None
    n = 0
    for s in mod["functions"]:
        stem = f"{s['st_value']:06x}"
        if want is not None and stem not in want:
            continue
        c = draft(mod, s["st_value"], s["st_value"] + s["size"], s["name"])
        if c:
            (out / f"{stem}.c").write_text(c, encoding="utf-8")
            n += 1
    print(f"{n} drafts -> {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
