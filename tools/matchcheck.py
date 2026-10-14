#!/usr/bin/env python3
"""Compare a compiled C object against the original function bytes (Phase 3/6).

This is a small, dependency-free replacement for objdiff at the *instruction*
level, tuned for this project:

* the original bytes come from the flat load image (`build/SCUS_974.72.rom`),
  addressed as `vaddr - 0x100000`;
* the trailing `nop` alignment padding that EE-GCC leaves after a function is
  stripped from the original before comparing (it is not part of the C codegen);
* relocation-dependent instruction fields (the 16-bit immediate of
  `%hi`/`%lo`/`%gp_rel`, the 26-bit target of `j`/`jal`) are masked out, because
  they are resolved by the linker against the final layout, not by the compiler.

Usage (from WSL or Windows):
    python3 tools/matchcheck.py --obj build/phase3/x/002FE0.o --case 002FE0
    python3 tools/matchcheck.py --objdir build/phase3/x --cases 002FE0 011FB8
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ROM = ROOT / "build" / "SCUS_974.72.rom"
COD = ROOT / "asm" / "cod"
ROM_BASE = 0x00100000

# ELF32/MIPS relocation types we care about (the bit field they patch)
REL_FIELD = {
    2: ("32", 0xFFFFFFFF),   # R_MIPS_32
    4: ("26", 0x03FFFFFF),   # R_MIPS_26
    5: ("HI16", 0x0000FFFF),  # R_MIPS_HI16
    6: ("LO16", 0x0000FFFF),  # R_MIPS_LO16
    7: ("GPREL16", 0x0000FFFF),  # R_MIPS_GPREL16
    8: ("LITERAL", 0x0000FFFF),  # R_MIPS_LITERAL
    9: ("GOT16", 0x0000FFFF),   # R_MIPS_GOT16
    11: ("CALL16", 0x0000FFFF),  # R_MIPS_CALL16
    12: ("GPREL32", 0xFFFFFFFF),  # R_MIPS_GPREL32
    16: ("HI16", 0x0000FFFF),
    17: ("LO16", 0x0000FFFF),
}


def parse_asm(name: str) -> dict:
    """Read the splat .s of a function -> {symbol, addr, size}."""
    path = COD / f"{name}.s"
    if not path.exists():
        raise FileNotFoundError(path)
    text = path.read_text(encoding="utf-8", errors="replace")
    sym = size = None
    for line in text.splitlines():
        if line.startswith("nonmatching "):
            rest = line[len("nonmatching "):]
            s, sz = rest.split(",")
            sym = s.strip()
            size = int(sz.strip(), 16)
        elif line.startswith("glabel ") and sym is None:
            sym = line.split()[1]
    return {"symbol": sym, "addr": int(name, 16) + ROM_BASE, "size": size}


def load_rom() -> bytes:
    if not ROM.exists():
        raise FileNotFoundError(
            f"{ROM} missing - run tools/make_rom.py (or the splat pipeline) first")
    return ROM.read_bytes()


def load_obj(path: Path) -> dict:
    """Minimal ELF32 little-endian reader: .text, visible symbols, relocs."""
    data = path.read_bytes()
    if data[:4] != b"\x7fELF":
        raise ValueError(f"{path}: not an ELF file")
    if data[4] != 1 or data[5] != 1:
        raise ValueError(f"{path}: not ELF32 little-endian")
    e_shoff, = struct.unpack_from("<I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    shs = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        shs.append(struct.unpack_from("<10I", data, off))
    strtab = shs[e_shstrndx]
    shstr = data[strtab[4]:strtab[4] + strtab[5]]

    def name_at(base: bytes, off: int) -> str:
        end = base.find(b"\0", off)
        return base[off:end].decode("utf-8", "replace")

    text = b""
    symtab = None
    symstr = b""
    rels: list[tuple[int, int, int]] = []
    out = {"text": b"", "symbols": {}, "relocs": [], "sections": []}
    for sh in shs:
        nm = name_at(shstr, sh[0])
        out["sections"].append(nm)
        if nm == ".text":
            text = data[sh[4]:sh[4] + sh[5]]
        elif nm == ".symtab":
            symtab = sh
            symstr = data[shs[sh[6]][4]:shs[sh[6]][4] + shs[sh[6]][5]]
        elif nm in (".rel.text", ".rela.text"):
            entsize = 12 if nm == ".rela.text" else 8
            for o in range(sh[4], sh[4] + sh[5], entsize):
                r_off, r_info = struct.unpack_from("<II", data, o)
                rels.append((r_off, r_info & 0xFF, r_info >> 8))
    out["text"] = text
    out["relocs"] = rels
    if symtab:
        for i in range(symtab[5] // symtab[9]):
            o = symtab[4] + i * symtab[9]
            st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from(
                "<IIIBBH", data, o)
            if st_name:
                out["symbols"][i] = {
                    "name": name_at(symstr, st_name),
                    "value": st_value,
                    "size": st_size,
                    "type": st_info & 0xF,
                }
    return out


def _reloc_mask(relocs: list, i: int) -> int:
    """Bit mask covering the bytes of instruction word i that a reloc patches."""
    if isinstance(relocs, dict):
        return relocs.get(i, 0)
    return 0


def compare(obj_path: Path, case: str, rom: bytes, *, verbose: bool = False) -> dict:
    info = parse_asm(case)
    sym, addr, size = info["symbol"], info["addr"], info["size"]
    orig = rom[addr - ROM_BASE: addr - ROM_BASE + size]
    if len(orig) != size:
        return {"case": case, "ok": False, "why": "original bytes out of range"}

    # strip trailing nop padding (not produced by the C compiler)
    body = orig
    while len(body) >= 4 and body[-4:] == b"\x00\x00\x00\x00":
        body = body[:-4]
    pad = orig[len(body):]

    obj = load_obj(obj_path)
    text = obj["text"]
    # locate the function inside the object
    start = 0
    idx = _find_sym(obj, sym)
    fsym = obj["symbols"].get(idx if idx is not None else -1)
    if fsym is None and obj["symbols"]:
        res = {"case": case, "symbol": sym, "addr": addr, "orig_size": size,
               "ok": False, "diffs": [],
               "why": f"object defines no symbol named {sym}"}
        return res
    if fsym:
        start = fsym["value"] - _text_vaddr(obj)
    mine = text[start:start + len(body)]

    res = {"case": case, "symbol": sym, "addr": addr,
           "orig_size": size, "code_size": len(body),
           "pad_bytes": len(pad), "compiled_size": len(text) - start,
           "relocs": [], "ok": False}
    for off, typ, si in obj["relocs"]:
        nm = obj["symbols"].get(si, {}).get("name", "?")
        res["relocs"].append({"off": off - start, "type": REL_FIELD.get(typ, (str(typ), 0))[0],
                              "sym": nm})

    if len(mine) != len(body):
        res["why"] = (f"size differs: original {len(body)} bytes, compiled "
                      f"{len(text) - start}")
        return res

    # byte masks from the relocation table
    masks = [0] * (len(body) // 4)
    for off, typ, si in obj["relocs"]:
        off -= start
        if off < 0 or off >= len(body):
            continue
        field = REL_FIELD.get(typ)
        if not field:
            continue
        masks[off // 4] |= field[1]

    diffs = []
    for i in range(0, len(body), 4):
        a, = struct.unpack_from("<I", body, i)
        b, = struct.unpack_from("<I", mine, i)
        if (a ^ b) & ~masks[i // 4]:
            diffs.append((i, a, b))
    res["diffs"] = [{"off": i, "orig": f"{a:08X}", "mine": f"{b:08X}"} for i, a, b in diffs]
    res["ok"] = not diffs
    if diffs and "why" not in res:
        res["why"] = f"{len(diffs)} instruction(s) differ"
    if verbose:
        for d in res["diffs"]:
            print(f"    ! +{d['off']:#04x}  orig {d['orig']}  mine {d['mine']}")
    return res


def _find_sym(obj: dict, name: str) -> int | None:
    for idx, s in obj["symbols"].items():
        if s["name"] == name:
            return idx
    return None


def _text_vaddr(obj: dict) -> int:
    # .text conventionally starts at 0 in a relocatable object
    return 0


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--obj")
    ap.add_argument("--objdir", type=Path)
    ap.add_argument("--case")
    ap.add_argument("--cases", nargs="*", default=[])
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--json", type=Path)
    args = ap.parse_args()

    rom = load_rom()
    cases = args.cases or ([args.case] if args.case else [])
    if args.objdir:
        cases = cases or sorted(p.stem for p in args.objdir.glob("*.o"))
    results = []
    for c in cases:
        obj = Path(args.obj) if args.obj else (args.objdir / f"{c}.o")
        if not obj.exists():
            print(f"{c}: NO OBJECT {obj}")
            results.append({"case": c, "ok": False, "why": "no object"})
            continue
        r = compare(obj, c, rom, verbose=args.verbose)
        results.append(r)
        status = "MATCH " if r["ok"] else "DIFF  "
        extra = "" if r["ok"] else f"  <- {r.get('why', '')}"
        print(f"{status} {c} {r.get('symbol', '?')} "
              f"code={r.get('code_size', 0)}B pad={r.get('pad_bytes', 0)}B{extra}")
        if args.verbose and r.get("relocs"):
            for rl in r["relocs"]:
                print(f"    reloc +{rl['off']:#04x} {rl['type']:<8} {rl['sym']}")
    n_ok = sum(1 for r in results if r["ok"])
    print(f"-- {n_ok}/{len(results)} match")
    if args.json:
        args.json.write_text(json.dumps(results, indent=1), encoding="utf-8")
    return 0 if n_ok == len(results) else 1


if __name__ == "__main__":
    sys.exit(main())
