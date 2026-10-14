#!/usr/bin/env python3
"""Compare the ELF *container* of the original vs our relinked build (step 6).

The flat load image already matches byte-for-byte (docs/rebuild.md); this tool
documents what still differs in the outer ELF file: program headers, the section
header table, and the debug/metadata sections (`.mdebug.eabi64`, `.reginfo`).

    python3 tools/elf_container_diff.py
    python3 tools/elf_container_diff.py --json build/container_diff.json
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ORIG = ROOT / "extracted" / "SCUS_974.72"
OURS = ROOT / "build" / "SCUS_974.72.elf"


def read_elf(path: Path) -> dict:
    d = path.read_bytes()
    (e_type, e_machine, e_version, e_entry, e_phoff, e_shoff, e_flags) = \
        struct.unpack_from("<HHIIIII", d, 16)
    e_ehsize, e_phentsize, e_phnum, e_shentsize, e_shnum, e_shstrndx = \
        struct.unpack_from("<HHHHHH", d, 40)
    phs = [struct.unpack_from("<8I", d, e_phoff + i * e_phentsize)
           for i in range(e_phnum)]
    shs = [struct.unpack_from("<10I", d, e_shoff + i * e_shentsize)
           for i in range(e_shnum)]
    shstr = d[shs[e_shstrndx][4]:shs[e_shstrndx][4] + shs[e_shstrndx][5]]

    def nm(off: int) -> str:
        end = shstr.find(b"\0", off)
        return shstr[off:end].decode("utf-8", "replace")

    return {
        "path": str(path),
        "bytes": len(d),
        "header": {"e_type": e_type, "e_machine": e_machine, "e_entry": e_entry,
                   "e_flags": e_flags, "e_phnum": e_phnum, "e_shnum": e_shnum,
                   "e_shstrndx": e_shstrndx, "e_phoff": e_phoff,
                   "e_shoff": e_shoff},
        "program_headers": [
            {"type": p[0], "offset": p[1], "vaddr": p[2], "paddr": p[3],
             "filesz": p[4], "memsz": p[5], "flags": p[6], "align": p[7]}
            for p in phs],
        "sections": [
            {"index": i, "name": nm(sh[0]), "type": sh[1], "flags": sh[2],
             "addr": sh[3], "offset": sh[4], "size": sh[5], "align": sh[8]}
            for i, sh in enumerate(shs)],
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", type=Path)
    ap.add_argument("--ours", type=Path, default=OURS,
                    help="ELF to compare against the original "
                         "(default: build/SCUS_974.72.elf)")
    args = ap.parse_args()
    ours = args.ours
    if not ORIG.exists() or not ours.exists():
        print(f"need both {ORIG} and {ours}")
        return 1

    a, b = read_elf(ORIG), read_elf(ours)
    print(f"original: {a['path']}  {a['bytes']} bytes")
    print(f"ours    : {b['path']}  {b['bytes']} bytes  "
          f"({b['bytes'] - a['bytes']:+d})")

    print("\nELF header differences:")
    for k in a["header"]:
        if a["header"][k] != b["header"][k]:
            print(f"  {k}: original {a['header'][k]} vs ours {b['header'][k]}")

    print(f"\nprogram headers: original {len(a['program_headers'])}, "
          f"ours {len(b['program_headers'])}")
    for i in range(max(len(a["program_headers"]), len(b["program_headers"]))):
        pa = a["program_headers"][i] if i < len(a["program_headers"]) else None
        pb = b["program_headers"][i] if i < len(b["program_headers"]) else None
        mark = "  " if pa == pb else "!!"
        print(f"  {mark} [{i}] orig {pa}")
        if pa != pb:
            print(f"       ours {pb}")

    na = [s["name"] for s in a["sections"]]
    nb = [s["name"] for s in b["sections"]]
    print(f"\nsections: original {len(na)}, ours {len(nb)}")
    print(f"  only in original: {[n for n in na if n not in nb]}")
    print(f"  only in ours    : {[n for n in nb if n not in na]}")
    print("  shared sections that differ:")
    bya = {s["name"]: s for s in a["sections"]}
    for s in b["sections"]:
        o = bya.get(s["name"])
        if not o:
            continue
        keys = [k for k in ("type", "flags", "addr", "offset", "size", "align")
                if o[k] != s[k]]
        if keys:
            print(f"    {s['name']:<18} differs in {keys}: "
                  f"orig {[o[k] for k in keys]} vs ours {[s[k] for k in keys]}")

    if args.json:
        args.json.write_text(json.dumps({"original": a, "ours": b}, indent=1),
                             encoding="utf-8")
        print(f"\nwrote {args.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
