#!/usr/bin/env python3
"""Phase 5: find which function references which string (evidence for naming).

Scans `.text` for `lui`/`%lo` address materialisations, resolves them to
absolute addresses, and maps each resolved address that coincides with a known
string (`manifest/strings.txt`) back to the splat function that contains the
reference. Output is a candidate `name <- string` list; nothing is renamed
automatically (see config/symbol_addrs.txt).

    python3 tools/find_string_refs.py                # all references
    python3 tools/find_string_refs.py --min-len 8    # only strings >= 8 chars
    python3 tools/find_string_refs.py --json build/string_refs.json
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
ROM_BASE = 0x00100000
STRINGS = ROOT / "manifest" / "strings.txt"


def load_strings() -> dict[int, str]:
    out: dict[int, str] = {}
    for line in STRINGS.read_text(encoding="utf-8", errors="replace").splitlines():
        m = re.match(r"^0x([0-9A-Fa-f]+)\s(.*)$", line)
        if m:
            out[int(m.group(1), 16)] = m.group(2)
    return out


def sign16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def scan(rom: bytes):
    """Yield (insn_index, resolved_address) for lui/%lo materialisations."""
    words = struct.unpack_from(f"<{len(rom) // 4}I", rom, 0)
    last_lui: dict[int, tuple[int, int]] = {}
    for i, w in enumerate(words):
        op = w >> 26
        rs, rt, rd = (w >> 21) & 0x1F, (w >> 16) & 0x1F, (w >> 11) & 0x1F
        imm = sign16(w & 0xFFFF)
        if op == 0x0F:
            last_lui[rt] = ((w & 0xFFFF) << 16, i)
            continue
        ent = last_lui.get(rs)
        if ent and i - ent[1] <= 6:
            yield i, ent[0] + imm
        if op == 0x00:
            last_lui.pop(rd, None)
        else:
            last_lui.pop(rt, None)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--min-len", type=int, default=4)
    ap.add_argument("--json", type=Path)
    args = ap.parse_args()

    strings = {a: s for a, s in load_strings().items() if len(s) >= args.min_len}
    rom = (ROOT / "build" / "SCUS_974.72.rom").read_bytes()
    subs = build.cod_subsegments()
    code = [(v, s, sp) for v, s, sp, k in subs if k in ("asm", "c")]

    refs: dict[str, list[dict]] = {}
    for idx, addr in scan(rom):
        if addr not in strings:
            continue
        va = ROM_BASE + idx * 4
        owner = ""
        for v, s, sp in code:
            if v <= va < v + sp:
                owner = s
                break
        if not owner:
            continue
        refs.setdefault(owner, []).append({"addr": f"0x{addr:08X}",
                                           "text": strings[addr]})
    for k in refs:
        seen = set()
        uniq = []
        for r in refs[k]:
            if r["addr"] not in seen:
                seen.add(r["addr"])
                uniq.append(r)
        refs[k] = uniq

    if args.json:
        args.json.write_text(json.dumps(refs, indent=1), encoding="utf-8")
        print(f"wrote {args.json}")
    print(f"{len(refs)} function(s) reference a string "
          f"({len(strings)} strings >= {args.min_len} chars considered)")
    for fn in sorted(refs, key=lambda k: int(k, 16)):
        print(f"  {fn}:")
        for r in refs[fn][:4]:
            print(f"      {r['addr']}  {r['text'][:72]!r}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
