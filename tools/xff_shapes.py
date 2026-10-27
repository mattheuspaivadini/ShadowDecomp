#!/usr/bin/env python3
"""Harvest the mechanically provable .XFF functions (named **and** stripped).

`tools/xff_autotry.py` only looks at the *unnamed* (static) gaps and only knows
the tail-call frames. This tool covers the other half of the cheap pool: the
named functions whose whole body is one of a handful of shapes that GCC emits
canonically, so the C can be derived from the instruction stream and *proved* by
recompiling it byte-exactly (relocations masked, `tools/xff_try.py` logic).

Shapes recognised (all self-contained, no control flow):
  ret-addr      lui rX,hi ; jr $ra ; addiu rX,rX,lo     -> return &G;
  ret-load      lui rX,hi ; jr $ra ; lw  rY,lo(rX)      -> return G;   (lb/lh/ld
                                                          variants, signed and
                                                          unsigned, pointer)
  ret-imm       addiu v0,zero,imm ; jr $ra ; nop        -> return imm;
  ret-zero      daddu v0,zero,zero ; jr $ra ; ...       -> return 0;
  empty         jr $ra ; nop                            -> {}
  store-arg     lui rX,hi ; sw a0,lo(rX) ; jr $ra ; nop -> void f(int v){G=v;}
  tail-call     frame + argument setup + `j target` (reuses xff_autotry)

Nothing is written unless the compiled body is byte-identical to the container,
so a shape that does not describe the original is simply not kept.

Usage (inside WSL, like every ee-gcc step):
    python3 tools/xff_shapes.py KERNEL --max-size 128 --jobs 4
    python3 tools/xff_shapes.py KERNEL --max-size 512 --write
"""
from __future__ import annotations

import argparse
import os
import struct
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import eegcc  # noqa: E402
import xff_try  # noqa: E402
import xffcheck  # noqa: E402
import xfflib  # noqa: E402

OVERLAYS = ROOT / "overlays"

JR_RA = 0x03E00008
NOP = 0x00000000


def op(w: int) -> int:
    return w >> 26


def rd(w: int) -> int:
    return (w >> 11) & 0x1F


def rs(w: int) -> int:
    return (w >> 21) & 0x1F


def rt(w: int) -> int:
    return (w >> 16) & 0x1F


def imm(w: int) -> int:
    v = w & 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def sext(v: int) -> int:
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def is_lui(w: int) -> bool:
    return op(w) == 0x0F


def is_addiu(w: int) -> bool:
    return op(w) == 0x09


def is_ori(w: int) -> bool:
    return op(w) == 0x0D


def is_store(w: int) -> bool:
    return op(w) in (0x28, 0x29, 0x2A, 0x2B, 0x3F)      # sb sh swl sw sd


def is_load(w: int) -> bool:
    return op(w) in (0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                     0x1A, 0x1B, 0x30, 0x37, 0x27, 0x1E, 0x1F, 0x26)


LOAD_C: dict[int, tuple[str, str]] = {
    0x20: ("int", ""),          # lb
    0x24: ("unsigned char", ""),  # lbu
    0x21: ("short", ""),        # lh
    0x25: ("unsigned short", ""),  # lhu
    0x23: ("int", ""),          # lw
    0x1B: ("unsigned int", ""),  # lwu
    0x37: ("unsigned long", ""),  # ld
    0x1F: ("unsigned long", ""),  # lwu? (0x1F = special2) - guarded by caller
}
STORE_C = {0x28: "char", 0x29: "short", 0x2B: "int", 0x3F: "unsigned long"}


def analyse(mod: dict, fn: dict) -> dict:
    """Decode the relocations of one function into section/offset facts.

    HI16/LO16 are stored as a pair (the addend lives in the LO16 field and the
    carry is resolved by the loader), so the two entries are folded into one
    resolved section offset here.
    """
    start, end = fn["st_value"], fn["st_value"] + fn["size"]
    text = mod["text"]
    words = [struct.unpack_from("<I", text, o)[0] for o in range(start, end, 4)]
    syms = {s["index"]: s for s in mod["symbols"]}
    secs = {s["index"]: s for s in mod["sections"]}
    rels: dict[int, dict] = {}
    pending: dict[int, tuple] = {}          # sym index -> (word index, hi imm)
    for r in mod["relocs"]:
        if not start <= r["offset"] < end:
            continue
        k = (r["offset"] - start) // 4
        s = syms[r["sym"]]
        w = struct.unpack_from("<I", text, r["offset"])[0]
        entry = {"type": r["type"], "field": r["field"][0],
                 "section": secs.get(s["shndx"], {}).get("name", "?"),
                 "sym": s["name"], "value": None}
        rels[k] = entry
        if r["type"] == 5:                  # HI16
            pending[r["sym"]] = (k, (w & 0xFFFF))
        elif r["type"] == 6:                # LO16
            lo = w & 0xFFFF
            hi = pending.pop(r["sym"], (None, 0))[1]
            if lo & 0x8000:
                hi += 1
            entry["value"] = ((hi << 16) + sext(lo)) & 0xFFFFFFFF
            for kk, e in rels.items():      # the matching HI16 gets the same value
                if e["sym"] == s["name"] and e["value"] is None and e["type"] in (5, 16):
                    e["value"] = entry["value"]
    return {"words": words, "rels": rels, "relocs": mod["relocs"],
            "start": start, "size": fn["size"]}


def data_symbol(rel: dict) -> str:
    """Stable image label for an unnamed section-relative data object."""
    if rel["sym"]:
        return rel["sym"]
    sec = {"data": "data", "bss": "bss", "rodata": "rodata", "sdata": "sdata",
           "sbss": "sbss", ".data": "data", ".bss": "bss",
           ".rodata": "rodata"}.get(rel["section"], rel["section"].strip("."))
    return f"D_kernel_{sec}_{rel['value']:04X}"


def variants(a: dict, fname: str) -> list[tuple[str, str, str]]:
    """(shape, evidence, C text) candidates for one function."""
    ws, rels = a["words"], a["rels"]
    n = len(ws)
    out: list[tuple[str, str, str]] = []
    if n == 2 and ws[0] == JR_RA and ws[1] == NOP:
        out.append(("empty", "`jr $ra; nop` - empty body", f"void {fname}(void) {{\n}}\n"))
        return out
    # ---- 4-word leaves -------------------------------------------------
    if n == 4:
        w0, w1, w2, w3 = ws
        r0 = rels.get(0, {})
        # store-arg-ret: lui rX,hi ; addiu $v0,$zero,imm ; jr $ra ; sw $aN,lo(rX)
        # a setter that also reports success
        if (is_lui(w0) and is_addiu(w1) and rs(w1) == 0 and rt(w1) == 2
                and w2 == JR_RA and is_store(w3) and rt(w0) == rs(w3) and r0
                and 4 <= rt(w3) <= 7):
            g = data_symbol(r0)
            const = imm(w1)
            for t in ("int", "unsigned int", "short", "char"):
                out.append(("store-arg-ret",
                            f"`lui` + `addiu $v0,$zero,{const}` + `jr $ra` + delay "
                            f"`sw $a{rt(w3) - 4},lo(...)` - stores the argument in "
                            f"{r0['section']}+{r0['value']:#x} and returns {const}",
                            f"extern {t} {g};\n\nint {fname}({t} v) {{\n"
                            f"    {g} = v;\n    return {const};\n}}\n"))
            return out
        return out
    # ---- 5-word leaves -------------------------------------------------
    if n == 5:
        w0, w1, w2, w3, w4 = ws
        r0 = rels.get(0, {})
        # member-load: lui rX,hi ; addiu rX,rX,lo ; lw $v0,off(rX) ; jr $ra ; delay
        # The explicit `addiu` means the base was materialised once, i.e. the source
        # indexed a *member* of a structured object, not `*(T *)(base + off)`.
        if (is_lui(w0) and is_addiu(w1) and rt(w1) == rs(w1) == rt(w0)
                and is_load(w2) and rs(w2) == rt(w1) and rt(w2) == 2
                and w3 == JR_RA and r0):
            base = data_symbol(r0)
            off = imm(w2)
            ins = {0x20: "lb", 0x24: "lbu", 0x21: "lh", 0x25: "lhu",
                   0x23: "lw", 0x37: "ld"}.get(op(w2), "lw")
            if w4 == NOP:
                form, tail = "returns the member", ""
            elif op(w4) == 0x0B and rs(w4) == 2 and rt(w4) == 2 and imm(w4) == 1:
                form, tail = "returns (member == 0)", " == 0"
            else:
                return out
            for t in ("int", "unsigned int", "short", "unsigned short",
                      "char", "unsigned char", "void *"):
                cast = "int" if t == "void *" else t
                struct = f"S_{base}"
                out.append(("member-load",
                            f"`lui`+`addiu` base {r0['section']}+{r0['value']:#x}, "
                            f"`{ins} $v0,{off:#x}` - {form} as `{t}`",
                            f"struct {struct} {{\n    char pad[{off:#x}];\n"
                            f"    {t} member;\n}};\n\n"
                            f"extern struct {struct} {base};\n\n"
                            f"int {fname}(void) {{\n"
                            f"    return {base}.member{tail};\n}}\n"))
            return out
        return out
    if n != 3 or ws[1] != JR_RA:
        return out
    w0, delay = ws[0], ws[2]
    r0 = rels.get(0, {})
    # ret-addr: lui rX,hi ; jr ; addiu rX,rX,lo
    if is_lui(w0) and is_addiu(delay) and rt(delay) == rs(delay) == rt(w0) and r0:
        g = data_symbol(r0)
        out.append(("ret-addr",
                    f"`lui $r{rt(w0)}` + `jr $ra` + delay `addiu` (HI16/LO16 "
                    f"{r0['section']}+{r0['value']:#x}) - returns the object address",
                    f"extern char {g}[];\n\nint {fname}(void) {{\n    return (int){g};\n}}\n"))
        return out
    # ret-load: lui rX,hi ; jr ; lw rY,lo(rX)
    if is_lui(w0) and is_load(delay) and rs(delay) == rt(w0) and r0:
        ins = {0x20: "lb", 0x24: "lbu", 0x21: "lh", 0x25: "lhu", 0x23: "lw",
               0x1B: "lbu?", 0x37: "ld"}.get(op(delay))
        base = LOAD_C.get(op(delay), (None, ""))[0]
        if ins and base and rt(delay) == 2:  # result in $v0
            g = data_symbol(r0)
            # the width/signedness are not recoverable from a masked immediate,
            # so every C type that emits the same load is tried in turn
            types = [base] + [t for t in ("int", "unsigned int", "short",
                                          "unsigned short", "char",
                                          "unsigned char", "unsigned long")
                              if t != base]
            for t in types:
                out.append(("ret-load",
                            f"`lui` + `jr $ra` + delay `{ins} $v0,lo(...)` against "
                            f"{r0['section']}+{r0['value']:#x} - returns that object "
                            f"as `{t}`",
                            f"extern {t} {g};\n\n{t} {fname}(void) {{\n"
                            f"    return {g};\n}}\n"))
            return out
    # ret-imm: addiu/ori v0,zero,imm ; jr ; nop
    if (is_addiu(w0) or is_ori(w0)) and rs(w0) == 0 and rt(w0) == 2 and delay == NOP:
        out.append(("ret-imm", f"`{('addiu' if is_addiu(w0) else 'ori')} $v0,$zero,"
                               f"{imm(w0):#x}` - constant return",
                    f"int {fname}(void) {{\n    return {imm(w0) if is_addiu(w0) else w0 & 0xFFFF};\n}}\n"))
        return out
    # ret-zero: daddu v0,zero,zero ; jr ; anything
    if w0 == 0x0000102D and rt(w0) == 2:
        out.append(("ret-zero", "`daddu $v0,$zero,$zero` - zero return",
                    f"int {fname}(void) {{\n    return 0;\n}}\n"))
        return out
    # store-arg: lui rX,hi ; sw a0,lo(rX) ; jr ; nop|addiu sp
    if is_lui(w0) and is_store(delay) and rt(w0) == rs(delay) and r0:
        st = STORE_C.get(op(delay))
        argreg = rt(delay)
        if st and 4 <= argreg <= 7:
            g = data_symbol(r0)
            idx = argreg - 4
            params = ", ".join(f"{st} a{i}" for i in range(idx + 1))
            out.append(("store-arg",
                        f"`lui` + `sw $a{idx},lo(...)` + `jr $ra` - writes the "
                        f"argument to {r0['section']}+{r0['value']:#x}",
                        f"extern {st} {g};\n\nvoid {fname}({params}) {{\n    {g} = a{idx};\n}}\n"))
            return out
    return out


def tail_variants(mod: dict, fn: dict, fname: str) -> list[tuple[str, str, str]]:
    """Named-function tail calls, via the xff_autotry frame decoder."""
    import xff_autotry as at
    start, size = fn["st_value"], fn["size"]
    out = []
    for label, body, _flags in at.variants(mod, start, size, fname):
        if label != "tail":
            continue
        out.append(("tail-call", "frame whose only work is a single tail `j`",
                    f"{body}"))
    return out


def try_function(args: tuple) -> dict:
    module, fn, _write = args
    mod = xfflib.load_module(module)
    stem = f"{fn['st_value']:06X}"
    fname = fn["name"]
    a = analyse(mod, fn)
    cands = variants(a, fname) or tail_variants(mod, fn, fname)
    if not cands:
        return {"stem": stem, "name": fname, "size": fn["size"], "shape": None}
    Path(eegcc.WORK).mkdir(parents=True, exist_ok=True)
    for shape, evidence, c_text in cands:
        r = xff_try.score(module, mod, stem, c_text, flags=["-G0"],
                          size=None, symbol=None, verbose=False)
        if r["ok"]:
            return {"stem": stem, "name": fname, "size": fn["size"], "shape": shape,
                    "source": c_text, "evidence": evidence, "addr": fn["st_value"]}
    return {"stem": stem, "name": fname, "size": fn["size"], "shape": None}


def write_source(module: str, stem: str, fn: dict, shape: str, evidence: str,
                 c_text: str) -> None:
    src_dir = OVERLAYS / module.lower() / "src"
    src_dir.mkdir(parents=True, exist_ok=True)
    header = (f"/* {module}.XFF @ 0x{fn['st_value']:06X} ({fn['size']} B) - {fn['name']}\n"
              f" * Shape `{shape}` recovered by tools/xff_shapes.py and proved by\n"
              f" * recompiling it byte-exactly (relocations masked).\n"
              f" * Evidence: {evidence}.\n"
              f" */\n")
    (src_dir / f"{stem}.c").write_text(header + c_text, encoding="utf-8")
    manifest = OVERLAYS / module.lower() / "c_sources.txt"
    have = manifest.read_text(encoding="utf-8")
    if f"\n{stem} =" not in have:
        with manifest.open("a", encoding="utf-8", newline="\n") as fh:
            fh.write(f"{stem} = src/{stem}.c -G0\n")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("--max-size", type=int, default=512)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--limit", type=int, default=0)
    args = ap.parse_args()

    module = args.module.upper()
    mod = xfflib.load_module(module)
    done = xffcheck.parse_manifest(module)
    todo = [f for f in mod["functions"]
            if f"{f['st_value']:06x}" not in done and f["size"] <= args.max_size]
    if args.limit:
        todo = todo[:args.limit]
    eegcc.stage_sources()
    print(f"{module}: {len(todo)} unmatched functions <= {args.max_size} B")

    wins = []
    with ProcessPoolExecutor(max_workers=args.jobs) as ex:
        for r in ex.map(try_function, [(module, f, args.write) for f in todo]):
            if r["shape"]:
                wins.append(r)
                print(f"  MATCH {r['stem']} {r['name']} ({r['size']} B, {r['shape']})")
    if args.write:
        for r in wins:
            write_source(module, r["stem"], {"st_value": r["addr"], "size": r["size"],
                                             "name": r["name"]},
                         r["shape"], r["evidence"], r["source"])
    print(f"{module}: {len(wins)} matched, {sum(w['size'] for w in wins)} B")
    return 0


if __name__ == "__main__":
    sys.exit(main())
