#!/usr/bin/env python3
"""Build the flat ROM image that splat's PS2 flow expects.

splat's `create_config` normally runs `objcopy -O binary` on the PS2 ELF to make
a flat `<basename>.rom`, then slices it by `start = section.offset - first_offset`
(see splat/util/ps2/ps2elfinfo.py). MinGW's objcopy cannot read a MIPS ELF, so this
script reproduces that layout directly instead.

Layout rules (mirroring ps2elfinfo.get_info):
  * only ALLOC sections are considered;
  * PROGBITS sections contribute bytes; NOBITS (.bss/.sbss) do not;
  * MIPS_REGINFO is skipped;
  * `first_offset` is the file offset of the first section when sections are
    sorted by offset -- for this ELF that yields a constant file<->vaddr delta,
    so bytes are placed at (vaddr - min_vaddr).

Usage:
    python tools/make_rom.py <elf> <out.rom>
"""

from __future__ import annotations

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elf_info import parse  # noqa: E402

SHF_ALLOC = 0x2
SHT_PROGBITS = 1
SHT_NOBITS = 8
SHT_MIPS_REGINFO = 0x70000006


def build(elF: str, out: str) -> tuple[int, int, int]:
    data, header, segments, sections, _syms = parse(elF)
    alloc = [s for s in sections if (s.flags & SHF_ALLOC) and s.size > 0
             and s.type not in (SHT_MIPS_REGINFO,)]
    # splat anchors on the first section by file offset.
    first_offset = min(s.offset for s in alloc)
    min_vaddr = min(s.addr for s in alloc)
    delta = first_offset - min_vaddr  # constant if file and vaddr are parallel

    rom_size = 0
    for s in alloc:
        if s.type == SHT_NOBITS:
            continue
        start = s.offset - first_offset
        rom_size = max(rom_size, start + s.size)

    buf = bytearray(rom_size)  # zero-filled (objcopy --gap-fill=0x00)
    for s in alloc:
        if s.type == SHT_NOBITS:
            continue
        start = s.offset - first_offset
        buf[start:start + s.size] = data[s.offset:s.offset + s.size]

    os.makedirs(os.path.dirname(os.path.abspath(out)), exist_ok=True)
    with open(out, "wb") as f:
        f.write(buf)
    return rom_size, first_offset, delta


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    size, first_offset, delta = build(sys.argv[1], sys.argv[2])
    import hashlib
    sha1 = hashlib.sha1(open(sys.argv[2], "rb").read()).hexdigest()
    print(f"wrote {sys.argv[2]}  size=0x{size:x} ({size} bytes)")
    print(f"first_offset=0x{first_offset:x}  file-vaddr delta=0x{delta:x}")
    print(f"sha1={sha1}")
