#!/usr/bin/env python3
"""Run m2c (matt-kempster/m2c) over split overlay asm to get shape drafts.

m2c knows plain MIPS-III, not the R5900 64-bit forms the EE compiler emits, so the
split `.s` is normalised first (daddu/dsubu -> addu/subu, `.word` SPECIAL ops
decoded). Output is a *hint* like the Ghidra pseudo-C: score it with xff_try.py.

    python tools/xff_m2c.py KERNEL 02D9B0 [02DC58 ...] --m2c <path-to-m2c>
    python tools/xff_m2c.py KERNEL --stems-file open.txt --out build/m2c/KERNEL
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ASM = {"KERNEL": ROOT / "build/plan/xff/kernel_asm",
       "MANAGER": ROOT / "build/plan/xff/manager_asm",
       "GAMECORE": ROOT / "build/plan/xff/gamecore_asm"}
REG = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4",
       "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9",
       "k0", "k1", "gp", "sp", "fp", "ra"]
SPECIAL = {0x21: "addu", 0x23: "subu", 0x24: "and", 0x25: "or", 0x26: "xor", 0x27: "nor",
           0x2A: "slt", 0x2B: "sltu", 0x2D: "addu", 0x2F: "subu", 0x0B: "movn", 0x0A: "movz"}
SHIFT = {0x00: "sll", 0x02: "srl", 0x03: "sra"}


def word(m: re.Match) -> str:
    w = int(m.group(1), 16)
    rs, rt, rd, sh, fn = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 63
    if w >> 26 == 0 and fn in SPECIAL:
        return f"{SPECIAL[fn]} ${REG[rd]}, ${REG[rs]}, ${REG[rt]}"
    if w >> 26 == 0 and fn in SHIFT:
        return f"{SHIFT[fn]} ${REG[rd]}, ${REG[rt]}, {sh}"
    return f".word 0x{w:08X}"


def normalise(text: str) -> str:
    rows = []
    targets = set()
    for ln in text.splitlines():
        m = re.search(r"/\*\s*([0-9A-Fa-f]+)\s+[0-9A-Fa-f]{8}\s*\*/", ln)
        addr = int(m.group(1), 16) if m else None
        ln = re.sub(r"/\*.*?\*/", "", ln)
        ln = re.sub(r"\.word\s+0x([0-9a-fA-F]+)", word, ln)
        ln = re.sub(r"\bdaddu\b", "addu", ln)
        ln = re.sub(r"\bdsubu\b", "subu", ln)
        ln = re.sub(r"\bdaddiu\b", "addiu", ln)
        t = re.search(r"\b(?:b\w*|j)\b.*?(0x[0-9a-fA-F]{4,})\s*$", ln)
        if t and ln.split()[0] != "jal":
            targets.add(int(t.group(1), 16))
            ln = ln[:t.start(1)] + ".L%X" % int(t.group(1), 16)
        if ln.strip():
            rows.append((addr, ln.rstrip()))
    out = []
    for addr, ln in rows:
        if addr in targets:
            out.append(".L%X:" % addr)
        out.append(ln)
    return "\n".join(out) + "\n"


def run(mod: str, stem: str, m2c: str, outdir: Path | None) -> str:
    src = next(ASM[mod].glob(f"{stem.upper()}_*.s"), None)
    if not src:
        return f"/* no asm for {stem} */"
    tmp = outdir / f"{stem}.s" if outdir else ROOT / "build" / f"_m2c_{stem}.s"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    tmp.write_text(normalise(src.read_text()))
    r = subprocess.run([sys.executable, "-s", m2c, "--target", "mipsel-gcc-c", str(tmp)], capture_output=True, text=True)
    res = r.stdout if r.returncode == 0 else f"/* m2c failed: {r.stderr.strip()[-300:]} */"
    if outdir:
        (outdir / f"{stem}.c").write_text(res)
    else:
        tmp.unlink(missing_ok=True)
    return res


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--stems-file")
    ap.add_argument("--out")
    ap.add_argument("--m2c", default="m2c.py")
    a = ap.parse_args()
    stems = list(a.stems)
    if a.stems_file:
        stems += Path(a.stems_file).read_text().split()
    outdir = Path(a.out) if a.out else None
    for s in stems:
        res = run(a.module, s, a.m2c, outdir)
        if not outdir:
            print(f"// ---- {s}\n{res}")


if __name__ == "__main__":
    sys.exit(main())
