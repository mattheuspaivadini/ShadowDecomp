#!/usr/bin/env python3
"""Shared reader for the .XFF overlay modules (KERNEL / MANAGER / GAMECORE).

The `.XFF` files are Team Ico `xff2` overlay containers that wrap a *relocatable*
ELF image, so they are not addressable like a linked executable:

* `.text` starts at its own section base; a function's address is its offset in
  `.text` (the stems used by this project are those offsets);
* every instruction field the loader patches is described by the `.text`
  relocation table (SHT_REL semantics: the addend is stored in the instruction),
  exactly as in an object file;
* the symbol table carries defined `.text` symbols (`st_shndx == 1`),
  `SHN_ABS` symbols that point into the boot ELF image (`0x001xxxxx`), and a few
  undefined imports.

Everything is parsed straight from the container, so no derived ELF has to be
trusted. Nothing here writes game bytes into the repository.

Format evidence: `docs/plan/scripts/xff_probe.py` (parsed from the boot ELF's own
loader: `DecodeSection`, `ResolveRelocation`, `RelocateElfInfoHeader`).
"""
from __future__ import annotations

import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EXTRACTED = ROOT / "extracted"

XFF_MAGIC = 0x32666678  # "xff2"

# ELF32/MIPS relocation types (the instruction field each one patches)
REL_FIELD = {
    2: ("32", 0xFFFFFFFF),      # R_MIPS_32
    4: ("26", 0x03FFFFFF),      # R_MIPS_26
    5: ("HI16", 0x0000FFFF),    # R_MIPS_HI16
    6: ("LO16", 0x0000FFFF),    # R_MIPS_LO16
    7: ("GPREL16", 0x0000FFFF),  # R_MIPS_GPREL16
    8: ("LITERAL", 0x0000FFFF),  # R_MIPS_LITERAL
    9: ("GOT16", 0x0000FFFF),    # R_MIPS_GOT16
    11: ("CALL16", 0x0000FFFF),  # R_MIPS_CALL16
    12: ("GPREL32", 0xFFFFFFFF),  # R_MIPS_GPREL32
    16: ("HI16", 0x0000FFFF),
    17: ("LO16", 0x0000FFFF),
}


def _cstr(buf: bytes, off: int) -> str:
    end = buf.find(b"\x00", off)
    if end < 0:
        end = len(buf)
    return buf[off:end].decode("utf-8", "replace")


def load_module(module: str) -> dict:
    """Parse `<module>.XFF` into text bytes, functions, symbols and relocations."""
    module = module.upper()
    path = EXTRACTED / f"{module}.XFF"
    if not path.exists():
        raise SystemExit(f"{path} missing - extract the ISO first")
    buf = path.read_bytes()
    h = struct.unpack_from("<28I", buf, 0)
    if h[0] != XFF_MAGIC:
        raise SystemExit(f"{module}.XFF: bad magic {h[0]:#x}")

    shnum, shoff = h[16], h[23]
    shstr_offs, shstrtab = h[26], h[27]
    sections = []
    for i in range(shnum):
        noff = struct.unpack_from("<I", buf, shstr_offs + i * 4)[0]
        s = struct.unpack_from("<8I", buf, shoff + i * 32)
        sections.append({
            "index": i,
            "name": _cstr(buf, shstrtab + noff),
            "addr": s[0],
            "disk_ptr": s[1],
            "size": s[2],
            "align": s[3],
            "sh_type": s[4],
            "file_offset": s[7],
        })
    by_name = {s["name"]: s for s in sections}

    # symbol table: 16 bytes/entry + a parallel u32 "resolved value" array
    symoff, stroff, symvaloff = h[21], h[22], h[24]
    symbols = []
    for i in range(h[9]):
        st_name, st_val, st_size, st_info, st_other, st_shndx = struct.unpack_from(
            "<IIIbbH", buf, symoff + i * 16)
        rval, = struct.unpack_from("<I", buf, symvaloff + i * 4)
        symbols.append({
            "index": i,
            "name": _cstr(buf, stroff + st_name),
            "st_value": st_val,
            "resolved": rval,
            "size": st_size,
            "bind": (st_info >> 4) & 0xF,
            "type": st_info & 0xF,
            "shndx": st_shndx,
        })

    # relocation tables (28-byte header each; ELF32_Rel entries)
    reloff = h[25]
    relocs = []
    for i in range(h[14]):
        r = struct.unpack_from("<7I", buf, reloff + i * 28)
        sh_type, count, target, _a, _b, entries = r[0], r[1], r[2], r[3], r[4], r[5]
        if target != 1:  # only .text matters for code
            continue
        for k in range(count):
            r_off, r_info = struct.unpack_from("<II", buf, entries + k * 8)
            relocs.append({
                "offset": r_off,
                "type": r_info & 0xFF,
                "sym": r_info >> 8,
                "field": REL_FIELD.get(r_info & 0xFF, (str(r_info & 0xFF), 0)),
            })
    relocs.sort(key=lambda x: x["offset"])

    text = buf[by_name[".text"]["file_offset"]:
               by_name[".text"]["file_offset"] + by_name[".text"]["size"]]

    funcs = [s for s in symbols if s["type"] == 2 and s["shndx"] == 1 and s["size"] > 0]
    funcs.sort(key=lambda s: s["st_value"])

    return {
        "module": module,
        "text": text,
        "text_size": len(text),
        "functions": funcs,
        "symbols": symbols,
        "relocs": relocs,
        "sections": sections,
    }


def mask_for(relocs: list, start: int, size: int) -> list[int]:
    """Per-word bit masks covering the fields the linker patches."""
    masks = [0] * ((size + 3) // 4)
    for r in relocs:
        off = r["offset"] - start
        if 0 <= off < size:
            masks[off // 4] |= r["field"][1]
    return masks


def func_bounds(mod: dict, off: int) -> tuple[int, int, str] | None:
    """Return (start, end, name) for the symbol starting at `off`."""
    for s in mod["functions"]:
        if s["st_value"] == off:
            return s["st_value"], s["st_value"] + s["size"], s["name"]
    return None
