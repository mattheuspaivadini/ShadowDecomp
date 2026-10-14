#!/usr/bin/env python3
"""Search the original ELF for compiler-revision breadcrumbs.

The original is stripped (no .symtab/.strtab) but retains `.mdebug.eabi64`
(GCC 2.9x mdebug). This scans all section bytes for version-like substrings
and prints the mdebug section layout, as independent evidence of the EE-GCC
generation that built the game.

    python3 tools/cc/find_compiler_strings.py extracted/SCUS_974.72
"""
from __future__ import annotations

import re
import struct
import sys
from pathlib import Path

PAT = re.compile(
    rb"(?:ee-)?gcc[ -]?[0-9]+(?:\.[0-9]+)*(?:[-\w.]*)?|"
    rb"[0-9]\.[0-9]{1,2}(?:\.[0-9]+)?-ee[-\w.]*|"
    rb"GCC[ :][0-9][\w. -]*|"
    rb"2\.9[0-9.]*|3\.2[-\w.]*|eabi64|mdebug|"
    rb"cygnus|FSF|GNU C", re.IGNORECASE)


def sections(data: bytes):
    e_shoff, = struct.unpack_from("<I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    shs = [struct.unpack_from("<10I", data, e_shoff + i * e_shentsize)
           for i in range(e_shnum)]
    shstr = data[shs[e_shstrndx][4]:shs[e_shstrndx][4] + shs[e_shstrndx][5]]

    def nm(off):
        end = shstr.find(b"\0", off)
        return shstr[off:end].decode("latin-1", "replace")
    return [(nm(sh[0]), sh) for sh in shs]


def main() -> int:
    path = Path(sys.argv[1] if len(sys.argv) > 1
                else "extracted/SCUS_974.72")
    data = path.read_bytes()
    print(f"# {path}  ({len(data)} bytes)")
    for name, sh in sections(data):
        blob = data[sh[4]:sh[4] + sh[5]]
        hits = sorted({m.group(0) for m in PAT.finditer(blob)})
        if hits:
            print(f"\n[{name}] size=0x{sh[5]:x}")
            for h in hits[:60]:
                print(f"   {h.decode('latin-1', 'replace')!r}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
