#!/usr/bin/env python3
"""Reproduce the original `SCUS_974.72` ELF *container* around our own image.

The flat load image already matches byte-for-byte (docs/rebuild.md); this tool
closes the remaining gap at the ELF-container level (Session 4, step 6). The
GNU `ld` output from `tools/build.py` is a single RWX `PT_LOAD` with one `.cod`
section; the original from ee-ld (Sony's linker) has three program headers, the
real EE-GCC section names, a `PT_MIPS_REGINFO` segment, `.mdebug.eabi64` and no
symbol table.

The two inputs are deliberately separated:

* **content**  - every loadable byte comes from *our* build: the `.cod` section
  produced by `tools/build.py` (assembled from the splat per-function `.s` and
  the matching C).  This is the part that is independently proven byte-exact.
* **layout**   - the section table / program headers / entry point are the
  linker's *policy*, recovered from the original ELF.  A linker script encodes
  exactly this information; because GNU `ld` cannot emit a `PT_MIPS_REGINFO`
  segment and splat routes `.text_nop`/`.reginfo`/`.ctors`/`.dtors`/`.eh_frame`
  through one `.data` subsegment (see docs/splat.md), the layout is applied here
  instead of in a linker script.

The `.reginfo` `$gp` word is *not* taken from `.cod` (splat zero-fills it, as
`splat`'s PS2 flow excludes `SHT_MIPS_REGINFO` from the flat ROM - see
tools/make_rom.py) but rebuilt from our linker's own `_gp` symbol, so the
original `0x00141D70` falls out of `_gp = cod_LIT4_START + 0x7FF0`.

Usage:
    python3 tools/containerize.py [--ld build/SCUS_974.72.ld.elf]
                                  [--orig extracted/SCUS_974.72]
                                  [--out build/SCUS_974.72.elf] [--check]

Exit status: 0 on success, 2 if the produced container is *not* byte-identical
to the original (a regression guard, not a hard requirement).
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elf_info import parse  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_LD = ROOT / "build" / "SCUS_974.72.ld.elf"
DEFAULT_ORIG = ROOT / "extracted" / "SCUS_974.72"
DEFAULT_OUT = ROOT / "build" / "SCUS_974.72.elf"

# The original's `.shstrtab` still lists `.symtab`/`.strtab` even though both
# section headers were removed by the final strip (the string table was not
# rebuilt). Reproducing the quirk is what makes the container byte-identical;
# the names are evidence read from the original file, not invented.
STALE_SHSTRTAB_NAMES = [b".symtab", b".strtab"]

EI_NIDENT = 16
EHDR_FMT = "<HHIIIIIHHHHHH"
PHDR_SIZE = 32
SHDR_FMT = "<IIIIIIIIII"
SHDR_SIZE = 40
# ELF32 section header indices are absolute file offsets; `sh_name` is an offset
# into `.shstrtab`.
SHT_NULL = 0
SHT_NOBITS = 8


def build_shstrtab(names: list[str]) -> tuple[bytes, dict[str, int]]:
    """Canonical string table; `.symtab`/`.strtab` kept first to match the
    original byte layout (see STALE_SHSTRTAB_NAMES)."""
    table = bytearray(b"\x00")
    offsets: dict[str, int] = {"": 0}
    for extra in STALE_SHSTRTAB_NAMES:
        offsets[extra.decode()] = len(table)
        table += extra + b"\x00"
    for name in names:
        if name in offsets:
            continue
        offsets[name] = len(table)
        table += name.encode() + b"\x00"
    return bytes(table), offsets


def reginfo_with_gp(content: bytes, gp: int) -> bytes:
    """Fill the `.reginfo` `$gp` word.

    EE `.reginfo` is 24 bytes; the first 20 are the register masks (all zero in
    the original) and bytes 20..23 hold the `$gp` value (evidence: the original
    file's `.reginfo` is `00*20 70 1d 14 00` == 0x00141D70).
    """
    buf = bytearray(content)
    if len(buf) >= 24:
        buf[20:24] = struct.pack("<I", gp)
    return bytes(buf)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--ld", type=Path, default=DEFAULT_LD,
                    help="raw ld output (single .cod/.cod_bss)")
    ap.add_argument("--orig", type=Path, default=DEFAULT_ORIG,
                    help="original ELF providing the container layout")
    ap.add_argument("--out", type=Path, default=DEFAULT_OUT)
    ap.add_argument("--check", action="store_true",
                    help="fail (exit 2) if the container is not byte-identical")
    args = ap.parse_args()

    if not args.ld.exists():
        print(f"containerize: missing ld output {args.ld}", file=sys.stderr)
        return 1
    if not args.orig.exists():
        print(f"containerize: missing original ELF {args.orig}", file=sys.stderr)
        return 1

    _ld_data, _ld_hdr, _ld_segs, ld_sections, ld_symbols = parse(str(args.ld))
    cod = next((s for s in ld_sections if s.name == ".cod"), None)
    if cod is None:
        print("containerize: no .cod section in the ld output", file=sys.stderr)
        return 1
    cod_bytes = _ld_data[cod.offset:cod.offset + cod.size]

    gp_sym = next((s for s in ld_symbols if s.name == "_gp"), None)
    gp = gp_sym.value if gp_sym else 0
    if not gp:
        print("containerize: no _gp symbol in the ld output", file=sys.stderr)
        return 1

    o_data, o_hdr, o_segs, o_sections, _o_syms = parse(str(args.orig))

    # --- section content --------------------------------------------------
    names = [s.name for s in o_sections]
    # The original's `.shstrtab` order is: the two stale symtab names (below),
    # then `.shstrtab` itself, then the sections in table order.
    ordered = [".shstrtab"] + [n for n in names if n and n != ".shstrtab"]
    shstr, shstr_off = build_shstrtab(ordered)
    if shstr != o_data[o_sections[o_hdr["shstrndx"]].offset:
                         o_sections[o_hdr["shstrndx"]].offset +
                         o_sections[o_hdr["shstrndx"]].size]:
        print("containerize: warning: regenerated .shstrtab differs from the "
              "original", file=sys.stderr)

    out = bytearray(len(o_data))
    # ELF header (byte-identical to the original except for what we recompute).
    out[0:EI_NIDENT] = o_data[0:EI_NIDENT]
    struct.pack_into(
        EHDR_FMT, out, 16,
        *struct.unpack_from(EHDR_FMT, o_data, 16))
    # Program headers: the layout, taken verbatim (they describe where the
    # bytes go, not what the bytes are).
    out[o_hdr["phoff"]:o_hdr["phoff"] + o_hdr["phnum"] * PHDR_SIZE] = \
        o_data[o_hdr["phoff"]:o_hdr["phoff"] + o_hdr["phnum"] * PHDR_SIZE]

    for s in o_sections:
        if s.type == SHT_NULL or s.type == SHT_NOBITS or s.size == 0:
            continue
        if s.name == ".shstrtab":
            content = shstr
        else:
            # Everything loadable is a slice of our own `.cod` image.
            rel = s.addr - cod.addr
            if not (0 <= rel and rel + s.size <= len(cod_bytes)):
                print(f"containerize: section {s.name} (0x{s.addr:x} "
                      f"size 0x{s.size:x}) is outside our .cod image",
                      file=sys.stderr)
                return 1
            content = cod_bytes[rel:rel + s.size]
            if s.name == ".reginfo":
                content = reginfo_with_gp(content, gp)
        out[s.offset:s.offset + s.size] = content

    # --- section header table --------------------------------------------
    for i, s in enumerate(o_sections):
        struct.pack_into(
            SHDR_FMT, out, o_hdr["shoff"] + i * SHDR_SIZE,
            shstr_off[s.name] if s.name else 0,
            s.type, s.flags, s.addr, s.offset, s.size, s.link, s.info,
            s.addralign, s.entsize)

    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_bytes(bytes(out))

    identical = bytes(out) == o_data
    print(f"containerize: wrote {args.out} ({len(out)} bytes)")
    print(f"  entry 0x{o_hdr['entry']:08x}  phdrs {o_hdr['phnum']}  "
          f"sections {o_hdr['shnum']}  gp 0x{gp:08x}")
    print(f"  byte-identical to original: {'YES' if identical else 'NO'}")
    if not identical:
        # First differing byte helps debugging without dumping whole files.
        for i, (a, b) in enumerate(zip(out, o_data)):
            if a != b:
                print(f"  first difference at 0x{i:x}: "
                      f"ours 0x{a:02x} vs original 0x{b:02x}")
                break
        if len(out) != len(o_data):
            print(f"  size: ours {len(out)} vs original {len(o_data)}")

    if args.check and not identical:
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
