#!/usr/bin/env python3
"""Try to decompile the *unnamed* (static) .XFF functions mechanically.

The three overlay modules ship a globals-only symbol table, so every `static`
function is unnamed (1.1 MB of code in total). This tool inventories the gaps
with `tools/xff_inventory.py`, then tries a small set of *structural templates*
against each candidate: wrapper/tail-call shapes, constant-argument wrappers,
call-and-spin loops and one-field leaves. Every generated body is compiled with
the pinned EE-GCC and compared byte-for-byte against the container (relocation
masked) — only the bodies that match are kept, so a template that does not fit
the original is simply rejected.

Usage:
    python tools/xff_autotry.py KERNEL --limit 40
    python tools/xff_autotry.py MANAGER --all --write
    wsl -d Ubuntu -u root -- bash -lc "cd <repo> && python3 tools/xff_autotry.py GAMECORE --all --write"
"""
from __future__ import annotations

import argparse
import csv
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import eegcc  # noqa: E402
import xffcheck  # noqa: E402
import xfflib  # noqa: E402
import xff_inventory as inv  # noqa: E402

OVERLAYS = ROOT / "overlays"
TMP = Path(eegcc.WORK) / "xff_autotry"


def frame_size(w: int) -> int | None:
    if (w >> 16) == 0x27BD and (w & 0xFFFF) & 0x8000:  # addiu sp,sp,-imm
        return 0x10000 - (w & 0xFFFF)
    return None


def is_sd_ra(w: int) -> bool:
    return (w >> 16) == 0xFFBF


def is_ld_ra(w: int) -> bool:
    return (w >> 16) == 0xDFBF


def is_unframe(w: int, size: int) -> bool:
    return (w >> 16) == 0x27BD and (w & 0xFFFF) == size


def jump_target(mod: dict, at: int) -> str | None:
    """Symbol name for the `j`/`jal` at `at` (relocation target)."""
    for r in mod["relocs"]:
        if r["offset"] == at and r["type"] == 4:
            s = mod["symbols"][r["sym"]]
            if s["name"]:
                return s["name"]
            # section-relative: the addend is in the instruction
            w = int.from_bytes(mod["text"][at:at + 4], "little")
            off = (w & 0x03FFFFFF) << 2
            for f in mod["functions"]:
                if f["st_value"] == off:
                    return f["name"]
            return f"func_{off:08X}"
    return None


def arg_setup(w: int) -> tuple[int, str] | None:
    """Decode a single argument-setup instruction -> (arg index, C expr)."""
    op, rs, rt = (w >> 26) & 0x3F, (w >> 21) & 0x1F, (w >> 16) & 0x1F
    imm = w & 0xFFFF
    simm = imm - 0x10000 if imm & 0x8000 else imm
    if op == 0x09 and rs == 0 and 4 <= rt <= 7:          # li aN, imm
        return rt - 4, str(simm)
    if op == 0 and (w & 0x3F) == 0x2D and 4 <= rt <= 7:  # move aN, aM
        return rt - 4, f"arg{rs - 4}" if 4 <= rs <= 7 else "0"
    if op == 0 and (w & 0x3F) == 0x21 and 4 <= rt <= 7 and rs == 0:
        return rt - 4, "0"
    if op == 0x23 and 4 <= rt <= 7:                      # lw aN, off(aM)
        return rt - 4, f"*(int *)(arg{rs - 4} + {simm:#x})"
    return None


def variants(mod: dict, off: int, size: int, fname: str) -> list[tuple[str, str, list[str]]]:
    """(label, C text, extra flags) candidates for one function."""
    text = mod["text"]
    words = [int.from_bytes(text[off + i:off + i + 4], "little")
             for i in range(0, size, 4)]
    n = len(words)
    out: list[tuple[str, str, list[str]]] = []
    if n < 3:
        return out
    fsz = frame_size(words[0])
    if fsz is None or not is_unframe(words[-1], fsz):
        return out
    body = words[1:-2]                       # between the frame and the `j`
    if n < 4 or (words[-2] >> 26) != 2:      # tail call: j S ; addiu sp (delay)
        return out
    target = jump_target(mod, off + (n - 2) * 4)
    if not target:
        return out
    args: dict[int, str] = {}
    for w in body:
        if is_sd_ra(w) or is_ld_ra(w) or w == 0:
            continue
        d = arg_setup(w)
        if d is None:
            return out
        args[d[0]] = d[1]
    maxidx = max(args) if args else -1
    passthrough = [i for i in range(maxidx + 1) if i not in args]
    call_args = ", ".join(args.get(i, f"arg{i}") for i in range(maxidx + 1))
    proto = ", ".join(f"int arg{i}" for i in passthrough)
    sig = f"void {fname}({proto})" if proto else f"void {fname}(void)"
    out.append(("tail", f"{sig} {{\n    {target}({call_args});\n}}\n", []))
    out.append(("tail-nosib", f"{sig} {{\n    {target}({call_args});\n}}\n",
                ["-fno-optimize-sibling-calls"]))
    return out


def try_one(module: str, mod: dict, cand: dict, stem: str) -> tuple[str, str, str] | None:
    size = cand["size"]
    fname = f"func_{stem}"
    for label, body, flags in variants(mod, cand["off"], size, fname):
        src = TMP / f"{module}_{stem}.c"
        src.parent.mkdir(parents=True, exist_ok=True)
        src.write_text(body, encoding="utf-8")
        obj = TMP / f"{module}_{stem}.o"
        err = eegcc.compile_c(str(src.relative_to(eegcc.WORK)), obj, ["-G0", *flags],
                              compiler=None, stage=False)
        if err:
            continue
        objd = xffcheck.eegcc_object(obj)
        sym = xffcheck.find_symbol(objd, fname)
        if sym is None:
            continue
        start = sym["value"]
        mine = objd["text"][start:start + size]
        orig = mod["text"][cand["off"]:cand["off"] + size]
        if len(mine) != size:
            continue
        masks = [a | b for a, b in zip(xfflib.mask_for(mod["relocs"], cand["off"], size),
                                       xffcheck._obj_masks(objd, start, size))]
        ok = True
        for i in range(0, size, 4):
            a = int.from_bytes(orig[i:i + 4], "little")
            b = int.from_bytes(mine[i:i + 4], "little")
            if (a ^ b) & ~masks[i // 4]:
                ok = False
                break
        if ok:
            return label, body, " ".join(flags)
    return None


def candidates(module: str, mod: dict) -> list[dict]:
    base = inv.ghidra_base(module, mod)
    named, gaps = inv.segments(mod)
    named_starts = {f["st_value"] for f in mod["functions"]}
    rows = list(csv.DictReader((ROOT / "build" / "plan" / "ghidra_out" / module /
                                "functions.tsv").open(encoding="utf-8"), delimiter="\t"))
    out = []
    for r in rows:
        off = int(r["addr"], 16) - base
        if off in named_starts:
            continue
        if not any(a <= off < b for a, b in gaps):
            continue
        out.append({"off": off, "size": int(r["size"]), "name": r["name"]})
    out.sort(key=lambda c: (c["size"], c["off"]))
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--write", action="store_true", help="write the matching C into the lane")
    ap.add_argument("--max-size", type=int, default=64)
    args = ap.parse_args()

    module = args.module.upper()
    mod = xfflib.load_module(module)
    cands = [c for c in candidates(module, mod) if c["size"] <= args.max_size]
    if not args.all:
        cands = cands[:args.limit or 40]

    eegcc.stage_sources()
    TMP.mkdir(parents=True, exist_ok=True)
    src_dir = OVERLAYS / module.lower() / "src"
    manifest = OVERLAYS / module.lower() / "c_sources.txt"
    wins = []
    for cand in cands:
        stem = f"{cand['off']:06X}"
        res = try_one(module, mod, cand, stem)
        if res is None:
            continue
        label, body, flags = res
        wins.append((stem, label, body, flags))
        if args.write:
            src_dir.mkdir(parents=True, exist_ok=True)
            (src_dir / f"{stem}.c").write_text(body, encoding="utf-8")
            line = f"{stem} = src/{stem}.c -G0 size={cand['size']:#x}" + (
                f" {flags}" if flags else "")
            have = manifest.read_text(encoding="utf-8")
            if f"\n{stem} =" not in have:
                with manifest.open("a", encoding="utf-8", newline="\n") as fh:
                    fh.write(line + "\n")
    print(f"{module}: {len(wins)}/{len(cands)} candidates matched a template "
          f"({args.max_size} B cap)")
    for stem, label, _body, flags in wins:
        print(f"  {stem} {label}{' ' + flags if flags else ''}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
