#!/usr/bin/env python3
"""Dependency-free ELF32 parser tuned for PS2 (MIPS R5900, little-endian) images.

Prints the ELF header, program headers (segments), section headers, the symbol
table (if present) and a string inventory. This is ground-truth from the bytes,
independent of any disassembler.

Usage:
    python tools/elf_info.py <elf> [--strings] [--json out.json]
"""

from __future__ import annotations

import json
import struct
import sys
from dataclasses import dataclass, field

# ELF constants we care about
PT = {0: "NULL", 1: "LOAD", 2: "DYNAMIC", 3: "INTERP", 4: "NOTE", 6: "PHDR",
      7: "TLS", 0x60000000: "NULL(ps2)", 0x70000000: "MIPS_REGINFO",
      0x70000001: "MIPS_OPTIONS", 0x70000002: "MIPS_ABIFLAGS"}
SHT = {0: "NULL", 1: "PROGBITS", 2: "SYMTAB", 3: "STRTAB", 4: "RELA", 5: "HASH",
       6: "DYNAMIC", 7: "NOTE", 8: "NOBITS", 9: "REL", 10: "SHLIB", 11: "DYNSYM",
       14: "INIT_ARRAY", 15: "FINI_ARRAY", 16: "PREINIT_ARRAY", 17: "GROUP",
       18: "SYMTAB_SHNDX", 0x70000001: "MIPS_DEBUG", 0x70000003: "MIPS_ABIFLAGS"}
STT = {0: "NOTYPE", 1: "OBJECT", 2: "FUNC", 3: "SECTION", 4: "FILE", 5: "COMMON",
       6: "TLS"}
STB = {0: "LOCAL", 1: "GLOBAL", 2: "WEAK"}

# MIPS e_flags decoding
EF_MIPS_ARCH = {0x00000000: "ARCH_1", 0x10000000: "ARCH_2", 0x20000000: "ARCH_3",
                0x30000000: "ARCH_4", 0x40000000: "ARCH_5", 0x50000000: "ARCH_32",
                0x60000000: "ARCH_64", 0x70000000: "ARCH_32R2",
                0x80000000: "ARCH_64R2", 0x90000000: "ARCH_32R6",
                0xa0000000: "ARCH_64R6"}
EF_MIPS_NOREORDER = 0x00000001
EF_MIPS_PIC = 0x00000002
EF_MIPS_CPIC = 0x00000004
EF_MIPS_ABI2 = 0x00000020
EF_MIPS_32BITMODE = 0x00000100
EF_MIPS_FP64 = 0x00000200
EF_MIPS_NAN2008 = 0x00000400
EF_MIPS_MACH = 0x00ff0000
EF_MIPS_ARCH_MASK = 0xf0000000
PT_MIPS_REGINFO = 0x70000000


@dataclass
class Section:
    index: int
    name: str
    type: int
    flags: int
    addr: int
    offset: int
    size: int
    link: int
    info: int
    addralign: int
    entsize: int


@dataclass
class Segment:
    index: int
    p_type: int
    offset: int
    vaddr: int
    paddr: int
    filesz: int
    memsz: int
    flags: int
    align: int


@dataclass
class Symbol:
    name: str
    value: int
    size: int
    info: int
    other: int
    shndx: int

    @property
    def bind(self) -> str:
        return STB.get(self.info >> 4, str(self.info >> 4))

    @property
    def typ(self) -> str:
        return STT.get(self.info & 0xf, str(self.info & 0xf))


def parse(path: str):
    with open(path, "rb") as f:
        data = f.read()
    if data[:4] != b"\x7fELF":
        raise SystemExit("not an ELF file")
    ei_class, ei_data = data[4], data[5]
    if ei_class != 1:
        raise SystemExit("only ELF32 supported here")
    endian = "<" if ei_data == 1 else ">"
    if endian == ">" and data[5] != 2:
        pass
    (e_type, e_machine, e_version, e_entry, e_phoff, e_shoff, e_flags,
     e_ehsize, e_phentsize, e_phnum, e_shentsize, e_shnum,
     e_shstrndx) = struct.unpack_from(endian + "HHIIIIIHHHHHH", data, 16)

    header = {
        "class": "ELF32", "data": "little" if ei_data == 1 else "big",
        "osabi": data[7], "abi_version": data[8],
        "type": e_type, "machine": e_machine, "version": e_version,
        "entry": e_entry, "phoff": e_phoff, "shoff": e_shoff,
        "flags": e_flags, "ehsize": e_ehsize, "phentsize": e_phentsize,
        "phnum": e_phnum, "shentsize": e_shentsize, "shnum": e_shnum,
        "shstrndx": e_shstrndx,
    }

    segments = []
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = \
            struct.unpack_from(endian + "IIIIIIII", data, off)
        segments.append(Segment(i, p_type, p_offset, p_vaddr, p_paddr,
                                p_filesz, p_memsz, p_flags, p_align))

    sections_raw = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        (sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link,
         sh_info, sh_addralign, sh_entsize) = struct.unpack_from(
            endian + "IIIIIIIIII", data, off)
        sections_raw.append((sh_name, sh_type, sh_flags, sh_addr, sh_offset,
                             sh_size, sh_link, sh_info, sh_addralign, sh_entsize))

    # section header string table
    shstr = b""
    if e_shstrndx < e_shnum:
        s = sections_raw[e_shstrndx]
        shstr = data[s[4]:s[4] + s[5]]

    def name_at(tab: bytes, off: int) -> str:
        if off >= len(tab):
            return ""
        end = tab.find(b"\x00", off)
        return tab[off:end].decode("latin-1") if end >= 0 else ""

    sections = []
    for i, s in enumerate(sections_raw):
        sections.append(Section(i, name_at(shstr, s[0]), s[1], s[2], s[3], s[4],
                                s[5], s[6], s[7], s[8], s[9]))

    # symbols
    symbols = []
    strtab = b""
    symtab = next((s for s in sections if s.type == 2), None)  # SHT_SYMTAB
    dynsym = next((s for s in sections if s.type == 11), None)
    for tab in (symtab, dynsym):
        if tab is None:
            continue
        if tab.link < len(sections):
            st = sections[tab.link]
            strtab = data[st.offset:st.offset + st.size]
        count = tab.size // (tab.entsize or 16)
        for i in range(count):
            off = tab.offset + i * (tab.entsize or 16)
            st_name, st_value, st_size, st_info, st_other, st_shndx = \
                struct.unpack_from(endian + "IIIBBH", data, off)
            symbols.append(Symbol(name_at(strtab, st_name), st_value, st_size,
                                  st_info, st_other, st_shndx))

    return data, header, segments, sections, symbols


def describe_flags(flags: int) -> list[str]:
    out = []
    arch = EF_MIPS_ARCH.get(flags & EF_MIPS_ARCH_MASK)
    if arch:
        out.append(arch)
    if flags & EF_MIPS_NOREORDER:
        out.append("NOREORDER")
    if flags & EF_MIPS_PIC:
        out.append("PIC")
    if flags & EF_MIPS_CPIC:
        out.append("CPIC")
    if flags & EF_MIPS_ABI2:
        out.append("ABI2(n32)")
    if flags & EF_MIPS_32BITMODE:
        out.append("32BITMODE")
    if flags & EF_MIPS_FP64:
        out.append("FP64")
    if flags & EF_MIPS_NAN2008:
        out.append("NAN2008")
    mach = flags & EF_MIPS_MACH
    if mach:
        out.append(f"MACH=0x{mach:02x}")
    return out


def extract_strings(data: bytes, min_len: int = 4):
    out = []
    cur = bytearray()
    start = 0
    for i, b in enumerate(data):
        if 32 <= b < 127:
            if not cur:
                start = i
            cur.append(b)
        else:
            if len(cur) >= min_len:
                out.append((start, cur.decode("latin-1")))
            cur = bytearray()
    if len(cur) >= min_len:
        out.append((start, cur.decode("latin-1")))
    return out


def main(argv: list[str]) -> int:
    if len(argv) < 2:
        print(__doc__, file=sys.stderr)
        return 2
    path = argv[1]
    want_strings = "--strings" in argv
    json_out = None
    if "--json" in argv:
        json_out = argv[argv.index("--json") + 1]

    data, header, segments, sections, symbols = parse(path)

    print("== ELF header ==")
    for k, v in header.items():
        print(f"  {k}: {v} (0x{v:x})" if isinstance(v, int) else f"  {k}: {v}")
    print(f"  e_flags decoded: {describe_flags(header['flags'])}")

    print("\n== Program headers (segments) ==")
    print(f"  {'idx':>3} {'type':>10} {'offset':>10} {'vaddr':>10} {'filesz':>10} {'memsz':>10} {'flags':>5}")
    for s in segments:
        t = PT.get(s.p_type, f"0x{s.p_type:x}")
        print(f"  {s.index:>3} {t:>10} 0x{s.offset:08x} 0x{s.vaddr:08x} 0x{s.filesz:08x} 0x{s.memsz:08x} {s.flags:>5}")

    print("\n== Sections ==")
    print(f"  {'#':>3} {'name':>16} {'type':>12} {'addr':>10} {'offset':>10} {'size':>10} {'flags':>8}")
    for s in sections:
        t = SHT.get(s.type, f"0x{s.type:x}")
        print(f"  {s.index:>3} {s.name:>16} {t:>12} 0x{s.addr:08x} 0x{s.offset:08x} 0x{s.size:08x} 0x{s.flags:08x}")

    info = {"header": header, "segments": [s.__dict__ for s in segments],
            "sections": [s.__dict__ for s in sections],
            "symbols": [s.__dict__ for s in symbols]}

    print(f"\n== Symbols ({len(symbols)}) ==")
    funcs = [s for s in symbols if (s.info & 0xf) == 2]
    objs = [s for s in symbols if (s.info & 0xf) == 1]
    print(f"  functions: {len(funcs)}  objects: {len(objs)}")
    for s in symbols[:200]:
        print(f"  0x{s.value:08x} {s.size:>6} {s.bind:>6} {s.typ:>8} {s.name}")
    if len(symbols) > 200:
        print(f"  ... ({len(symbols)-200} more)")

    if want_strings:
        strings = extract_strings(data, 4)
        info["strings"] = [{"offset": o, "text": t} for o, t in strings]
        print(f"\n== Strings ({len(strings)}) ==")
        for o, t in strings[:300]:
            print(f"  0x{o:06x}  {t}")

    if json_out:
        with open(json_out, "w", encoding="utf-8") as f:
            json.dump(info, f, indent=2)
        print(f"\nwrote {json_out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
