#!/usr/bin/env python3
"""Inventory every absolute access to the EE hardware register space.

Evidence for the hardware-register identifications in `docs/structs.md`. The
tool reads the per-function disassembly under `asm/cod/` (splat/spimdisasm
output, which is the same text that is assembled for the byte-exact rebuild) and
reconstructs, per function, the absolute addresses built by `lui`+immediate
pairs. Only accesses whose resolved address lies outside the image (i.e. NOT in
`.text`/`.data`/`.bss`) are hardware/register-block references.

The point of doing this over the whole image instead of looking at one function
is *context*: which register addresses appear next to each other tells you which
block a candidate belongs to (e.g. a function that touches 0x1000F180 AND
0x1000E060 is a SIF/DMAC routine, not a GS routine).

Usage:
    python3 tools/scan_hw_regs.py                  # summarise 0x10000000-0x13FFFFFF
    python3 tools/scan_hw_regs.py --addr 0x1000E060
    python3 tools/scan_hw_regs.py --func func_00114C30
    python3 tools/scan_hw_regs.py --json build/hw_regs.json
"""
from __future__ import annotations

import argparse
import json
import re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ASM = ROOT / "asm" / "cod"

# image extents (see docs/structs.md "Section layout")
IMAGE_LO, IMAGE_HI = 0x00100000, 0x0016A328
HW_LO, HW_HI = 0x10000000, 0x14000000

# `    /* 14C30 00114C30 0010033C */  lui  $v1, ...`
# field 1 is the offset from the ROM base (no fixed width), field 2 the vaddr.
LINE = re.compile(
    r"^\s*/\*\s+([0-9A-Fa-f]{1,8})\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s+(\S+)\s*(.*)$"
)
# `lui $v1, (0x1000E060 >> 16)` / `lui $v0, %hi(D_00133920)` / `lui $a0, 0x1000`
LUI_EXPR = re.compile(r"^\(\s*(0x[0-9A-Fa-f]+)\s*>>\s*16\s*\)$")
LUI_HI = re.compile(r"^%hi\(\s*([A-Za-z_0-9]+)\s*\)$")
LUI_PLAIN = re.compile(r"^0x([0-9A-Fa-f]+)$")
IMM_EXPR = re.compile(r"^\(\s*0x[0-9A-Fa-f]+\s*&\s*0xFFFF\s*\)$")
LO_EXPR = re.compile(r"^%lo\(\s*([A-Za-z_0-9]+)\s*\)$")
# `lw $v0, 0x0($v1)` / `lw $v1, (0x10001010 & 0xFFFF)($v1)` / `lw $a0, %lo(D)($v0)`
MEMOP = re.compile(
    r"^(?P<op>lw|sw|lh|lhu|sh|lb|lbu|sb|ld|sd|ldl|ldr|sdl|sdr|lwl|lwr|swl|swr|lwc1|swc1|ldc1|sdc1|lqc2|sqc2|lwc2|swc2|ll|sc|lq|sq)"
    r"\s+\$(?P<dst>[a-z0-9]+),\s*(?P<off>\S+?)\((?P<base>\$[a-z0-9]+)\)$"
)
REG = re.compile(r"^\$([a-z0-9]+)$")

READ_OPS = {"lw", "lh", "lhu", "lb", "lbu", "ld", "ldl", "ldr", "lwl", "lwr",
            "lwc1", "ldc1", "lqc2", "lwc2", "ll", "lq"}
WRITE_OPS = {"sw", "sh", "sb", "sd", "sdl", "sdr", "swl", "swr", "swc1",
             "sdc1", "sqc2", "swc2", "sc", "sq"}


def signed16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def parse_functions() -> dict[str, list[tuple[int, str, list[str]]]]:
    """{func_name: [(vaddr, mnemonic, operands), ...]} from asm/cod/*.s."""
    out: dict[str, list[tuple[int, str, list[str]]]] = {}
    for path in sorted(ASM.glob("*.s")):
        insns: list[tuple[int, str, list[str]]] = []
        name = None
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            m = re.match(r"^\s*glabel\s+(\S+)$", line)
            if m:
                name = m.group(1)
                continue
            lm = LINE.match(line)
            if lm and name:
                vaddr = int(lm.group(2), 16)
                mnem = lm.group(4)
                ops = [o.strip() for o in lm.group(5).split(",")] if lm.group(5).strip() else []
                insns.append((vaddr, mnem, ops))
        if name and insns:
            out[name] = insns
    return out


def resolved_imm(func: str, operands: list[str], imm: str) -> int | None:
    """The 16-bit immediate of a `%lo(...)`/`(0x... & 0xFFFF)`/`0x...` operand."""
    if IMM_EXPR.match(imm):
        return int(re.search(r"0x([0-9A-Fa-f]+)", imm).group(1), 16)
    m = LO_EXPR.match(imm)
    if m:
        return None  # a linker symbol, not a hardware constant
    m = LUI_PLAIN.match(imm)
    if m:
        return int(m.group(1), 16)
    try:
        return signed16(int(imm, 0) & 0xFFFF)
    except ValueError:
        return None


def scan() -> dict:
    funcs = parse_functions()
    regs: dict[int, dict] = defaultdict(
        lambda: {"reads": 0, "writes": 0, "funcs": Counter(), "kinds": Counter()}
    )
    per_func: dict[str, Counter] = defaultdict(Counter)

    for fname, insns in funcs.items():
        # register -> high half materialised by lui (only while not clobbered)
        hi: dict[str, int] = {}
        # (addr) -> register that last loaded from it, for read-modify-write
        loaded: dict[int, str] = {}

        for vaddr, mnem, ops in insns:
            # --- lui: record the high half ---
            if mnem == "lui" and len(ops) == 2:
                dst = ops[0].lstrip("$")
                src = ops[1].strip()
                m = LUI_EXPR.match(src)
                val = None
                if m:
                    # `(0x1000E060 >> 16)` -> the *shifted* high half
                    val = ((int(m.group(1), 16) >> 16) & 0xFFFF) << 16
                else:
                    m = LUI_HI.match(src)
                    if m:
                        if m.group(1).startswith("D_"):
                            val = (int(m.group(1)[2:], 16) >> 16) << 16
                        else:
                            val = None  # named C symbol: not a hardware const
                    elif LUI_PLAIN.match(src):
                        val = (int(m.group(1), 16) & 0xFFFF) << 16
                hi[dst] = val
                loaded.pop(vaddr, None)
                continue

            # --- memory access ---
            mm = MEMOP.match(f"{mnem} " + ", ".join(ops))
            if mm:
                op = mm.group("op")
                base = mm.group("base").lstrip("$")
                dst = mm.group("dst")
                base_hi = hi.get(base)
                if base_hi is not None:
                    off = resolved_imm(fname, ops, mm.group("off"))
                    if off is not None:
                        # loads/stores take a *signed* 16-bit displacement,
                        # `lui $at,(X>>16)` + `lw -0x1000($at)` = X.
                        addr = (base_hi + signed16(off & 0xFFFF)) & 0xFFFFFFFF
                        if HW_LO <= addr < HW_HI:
                            rec = regs[addr]
                            rec["funcs"][fname] += 1
                            rec["kinds"][op] += 1
                            per_func[fname][hex(addr)] += 1
                            if op in READ_OPS:
                                rec["reads"] += 1
                                loaded[addr] = dst
                            elif op in WRITE_OPS:
                                rec["writes"] += 1
                                src = dst  # the stored register is the value reg
                                # read-modify-write: same reg loaded from this
                                # address earlier inside this function
                                if loaded.get(addr) == src:
                                    rec["kinds"]["rmw"] += 1
                # a load clobbers dst
                if op in READ_OPS:
                    hi.pop(dst, None)
                continue

            # --- ori $r, $r, low half: completes a lui address ---
            if mnem in ("ori", "addiu", "addi") and len(ops) == 3:
                dst = ops[0].lstrip("$")
                src = ops[1].lstrip("$")
                if dst == src and dst in hi and hi[dst] is not None:
                    imm = resolved_imm(fname, ops, ops[2])
                    if imm is not None:
                        if mnem == "ori":
                            addr = hi[dst] | (imm & 0xFFFF)
                        else:  # addiu/addi take a signed immediate
                            addr = (hi[dst] + signed16(imm & 0xFFFF)) & 0xFFFFFFFF
                        if HW_LO <= addr < HW_HI:
                            per_func[fname][hex(addr)] += 1
                            regs[addr]["funcs"][fname] += 1
                            regs[addr]["kinds"]["addr"] += 1
                        hi[dst] = addr  # the full address is now in the register
                elif dst in hi:
                    hi[dst] = None
                continue

            # --- anything else that writes a GPR invalidates its high half ---
            if mnem in ("jal", "jalr", "jr", "j", "b", "beq", "bne", "blez",
                        "bgtz", "bltz", "bgez", "beql", "bnel", "blezl",
                        "bgtzl", "bltzl", "bgezl"):
                continue
            for o in ops:
                r = REG.match(o.strip())
                if r and r.group(1) in hi:
                    hi[r.group(1)] = None

    return {
        "registers": {
            hex(a): {
                "reads": r["reads"],
                "writes": r["writes"],
                "kinds": dict(r["kinds"]),
                "functions": dict(r["funcs"].most_common()),
            }
            for a, r in sorted(regs.items())
        },
        "per_function": {f: dict(c.most_common()) for f, c in sorted(per_func.items())},
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--addr", help="show only this address (0x...)")
    ap.add_argument("--func", help="show only this function")
    ap.add_argument("--json", type=Path, help="write the full inventory as JSON")
    ap.add_argument("--all", action="store_true",
                    help="list every function with a register reference")
    args = ap.parse_args()

    data = scan()
    regs = data["registers"]

    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(json.dumps(data, indent=2), encoding="utf-8")
        print(f"wrote {args.json}")

    if args.addr:
        a = hex(int(args.addr, 16))
        rec = regs.get(a)
        if not rec:
            print(f"{args.addr}: no access found")
            return 1
        print(f"{a}: {rec['reads']} read(s), {rec['writes']} write(s), kinds={rec['kinds']}")
        for f, n in rec["functions"].items():
            print(f"  {f}  x{n}  ({', '.join(f'{k}={v}' for k, v in data['per_function'][f].items() if k == a)})")
        return 0

    if args.func:
        fn = args.func
        if fn not in data["per_function"]:
            print(f"{fn}: no hardware-register access found")
            return 1
        print(f"{fn}:")
        for a, n in data["per_function"][fn].items():
            rec = regs[a]
            print(f"  {a}  x{n}  reads={rec['reads']} writes={rec['writes']} kinds={rec['kinds']}")
        return 0

    print(f"hardware-register addresses referenced: {len(regs)}")
    print(f"{'address':<12}{'r':>4}{'w':>4}  kinds                        top functions")
    for a, rec in regs.items():
        top = ", ".join(list(rec["functions"])[:3])
        kinds = ",".join(f"{k}:{v}" for k, v in sorted(rec["kinds"].items()) if k != "addr")
        print(f"{a:<12}{rec['reads']:>4}{rec['writes']:>4}  {kinds:<28} {top}")
    if args.all:
        print("\nper function:")
        for f, c in data["per_function"].items():
            print(f"  {f:<20} {' '.join(c)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
