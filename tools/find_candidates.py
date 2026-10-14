#!/usr/bin/env python3
"""Rank the splat per-function .s files as Phase-3/6 decompilation candidates.

A "candidate" here is a small *leaf* function (no `jal`/`jalr`, no tail-call
`j` to another address) whose body avoids hard-to-express constructs
(CP0/COP2/VU0, MMI 128-bit ops, syscall/eret/cache, unaligned lh/lwl pairs...).

Usage:
    python3 tools/find_candidates.py [--limit N] [--max-insns N] [--json out]
"""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
COD = ROOT / "asm" / "cod"

# match:  /* <hex off> <addr> <word> */  <maybe indent> <mnemonic> <rest>
LINE = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s*\*/\s*(\S+)(?:\s+(.*?))?\s*$"
)
GLABEL = re.compile(r"^glabel\s+(\S+)")
ENLABEL = re.compile(r"^endlabel\s+(\S+)")

HARD = {
    # privileged / coprocessor-0
    "syscall", "break", "eret", "tlbr", "tlbwi", "tlbwr", "tlbp", "cache",
    "ei", "di", "mfc0", "mtc0", "cfc0", "ctc0", "mfsa", "mtsa", "rfe",
    # COP1
    "lwc1", "swc1", "ldc1", "sdc1", "cfc1", "ctc1", "mfc1", "mtc1", "bc1t",
    "bc1f", "add.s", "sub.s", "mul.s", "div.s", "sqrt.s", "cvt.s.w", "cvt.w.s",
    "adda.s", "madd.s", "msub.s", "mula.s", "mov.s", "neg.s", "abs.s", "c.eq.s",
    "c.lt.s", "c.le.s", "madda.s", "msuba.s", "div.s",
    # COP2 / VU0 macro mode
    "qmfc2", "qmtc2", "cfc2", "ctc2", "vadd", "vsub", "vmul", "vdiv", "vcallms",
    "vcallmsr", "lqc2", "sqc2", "vftoi", "vitof", "vmax", "vmini", "vdots",
    "vopmula", "vopmsub", "vclipw",
    # MMI (128-bit / packed)
    "lq", "sq", "lqc2", "sqc2", "paddw", "psubw", "paddh", "psubh", "paddb",
    "paddsw", "paddsh", "paddsb", "psubsw", "psubsh", "psubsb", "pcpyld",
    "pcpyud", "pcpyh", "pexew", "ppacw", "ppach", "ppacb", "pextlw", "pextuw",
    "pextlh", "pextuh", "pextlb", "pextub", "pinteh", "pintoh", "pmfhi",
    "pmflo", "pmthi", "pmtlo", "por", "pxor", "pnor", "pand", "pceqw", "pceqh",
    "pceqb", "pcgtw", "pcgth", "pcgtb", "pmaxw", "pmaxh", "pminw", "pminh",
    "pmaddw", "pmaddh", "pmaddb", "pmadduw", "pmsubw", "pmsubh", "pmsubb",
    "pmultw", "pmulth", "pmultuw", "pdivw", "pdivbw", "pdivuw", "pmfhi",
    "psllh", "psrlh", "psrah", "psllw", "psrlw", "psraw", "pabsh", "pabsw",
    "plzcw", "pexch", "pexcw", "prot3w", "mfsa", "mtsa",
    # 64-bit mult/div (needs 128-bit care but expressible; keep as soft flag)
}
SOFT = {"mult", "multu", "div", "divu", "dmult", "dmultu", "ddiv", "ddivu",
        "mfhi", "mflo", "mthi", "mtlo", "mult1", "div1", "madd", "msub"}
UNALIGNED = {"lwl", "lwr", "swl", "swr", "ldl", "ldr", "sdl", "sdr"}


def parse(path: Path):
    name = None
    insns: list[tuple[str, str]] = []
    for raw in path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = GLABEL.match(raw)
        if m:
            name = m.group(1)
            continue
        m = LINE.match(raw)
        if m and name:
            insns.append((m.group(1).lower(), (m.group(2) or "").strip()))
    return name, insns


def analyse(path: Path):
    name, insns = parse(path)
    if not name or not insns:
        return None
    mnems = [m for m, _ in insns]
    hard = sorted({m for m in mnems if m in HARD})
    soft = sorted({m for m in mnems if m in SOFT})
    unal = sorted({m for m in mnems if m in UNALIGNED})
    calls = sum(1 for m in mnems if m in ("jal", "jalr"))
    tailjumps = [t for m, t in insns if m == "j"]
    tailcall = [t for t in tailjumps if not t.startswith(".L")]
    return {
        "file": path.name,
        "name": name,
        "insns": len(insns),
        "bytes": len(insns) * 4,
        "hard": hard,
        "soft": soft,
        "unaligned": unal,
        "calls": calls,
        "tailcalls": len(tailcall),
    }


def score(c: dict) -> tuple:
    # prefer: leaf, no hard ops, small, no unaligned, no soft mult/div
    return (bool(c["hard"]), c["calls"] > 0, c["tailcalls"],
            bool(c["unaligned"]), bool(c["soft"]), c["insns"])


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--limit", type=int, default=40)
    ap.add_argument("--max-insns", type=int, default=24)
    ap.add_argument("--json", type=str, default="")
    ap.add_argument("--all", action="store_true", help="include non-leaf/hard functions")
    args = ap.parse_args()

    cands = [c for c in (analyse(p) for p in sorted(COD.glob("*.s"))) if c]
    print(f"{len(cands)} functions parsed")
    pool = cands if args.all else [
        c for c in cands
        if not c["hard"] and c["calls"] == 0 and c["tailcalls"] == 0
        and not c["unaligned"] and c["insns"] <= args.max_insns
    ]
    pool.sort(key=score)
    print(f"{len(pool)} leaf candidates (<= {args.max_insns} insns, no hard ops)")
    for c in pool[: args.limit]:
        note = []
        if c["soft"]:
            note.append("soft:" + ",".join(c["soft"]))
        print(f"  {c['file']:<10} {c['name']:<18} {c['insns']:>3} insn  "
              f"{' '.join(note)}")
    if args.json:
        Path(args.json).write_text(json.dumps(pool, indent=1), encoding="utf-8")
        print(f"wrote {args.json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
