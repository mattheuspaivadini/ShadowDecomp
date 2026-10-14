#!/usr/bin/env python3
"""Phase 5: derive function names from the strings a function references.

Evidence source: splat's *own* relocation analysis. Every `.s` file under
`asm/cod/` carries the labels spimdisasm paired for `lui`/`addiu`/`%lo`
(`%hi(D_00136A20)` ... `%lo(D_00136A20)`), so the string -> function mapping is
read straight from the disassembly instead of a `lui`-window heuristic (which
misses pairs that a branchy function spreads far apart - e.g. the `lui` at
0x00102DF4 and its `addiu` at 0x00102F00 in `func_00102D70`).

Two evidence classes are extracted from `manifest/strings.txt`:

* **verbatim**: the string is the routine's own diagnostic and contains its
  identifier (`"ldsys: setNewIopIdentifier: ..."`, `"sceDbcSendData2: rpc
  error\\n"`), or the identifier is passed as the message's own `%s` argument
  (`"sceSifMCallRpc"`), or the string is libc's in-function assert
  (`"bug in vfprintf: bad base"`).
* **object**: the string is a semaphore/thread name the function hands to the
  kernel's create call (`SceStdioReadSema`, `SceCdCallbackThread`). It names the
  *object*, not necessarily the routine, so it is reported separately and must
  be marked UNCONFIRMED.

Nothing is written to `config/symbol_addrs.txt` automatically; the output is
review material for `docs/naming-candidates.md`.

    python3 tools/name_from_strings.py
    python3 tools/name_from_strings.py --class object
    python3 tools/name_from_strings.py --json build/name_candidates.json
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ROM_BASE = 0x00100000
STRINGS = ROOT / "manifest" / "strings.txt"
ASM = ROOT / "asm" / "cod"

# Message prefixes that name a *library*/module, not a routine.
LIBRARY_TAGS = {
    "ld", "ldsys", "ldnet", "libdma", "libdbc", "libmc2", "libpad2", "libnet",
    "libcdvd", "libsif", "libvif", "libgif", "libgs", "libgraph", "ee", "rom0",
    "cdrom0", "entry", "cause", "bva", "spad", "kernel", "rom1", "dbcman",
    "fno", "msif", "in", "or", "start_menu",
}

SELF_PREFIX = re.compile(r"^(?P<name>[A-Za-z_][A-Za-z0-9_]{3,})\s*:")
TAGGED_PREFIX = re.compile(
    r"^(?P<tag>ldsys|ldnet|ld)\s*:\s*(?P<name>[A-Za-z_][A-Za-z0-9_]{3,})\s*:")
OBJECT = re.compile(r"^(?P<name>Sce[A-Za-z0-9_]*?)(?:Sema|Thread)$")
BARE_IDENT = re.compile(r"^(?P<name>[Ss]ce[A-Za-z0-9_]{3,})$")
ASSERT = re.compile(r"\b(?P<name>vfprintf)\b")

# Any label splat emitted inside a %hi()/%lo() or as a bare D_<hex> operand.
LABEL = re.compile(r"\b(D_[0-9A-Fa-f]{8})\b")
SYMBOL = re.compile(r"%hi\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)|%lo\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)")


def load_strings() -> dict[int, str]:
    out: dict[int, str] = {}
    for line in STRINGS.read_text(encoding="utf-8", errors="replace").splitlines():
        m = re.match(r"^0x([0-9A-Fa-f]+)\s(.*)$", line)
        if m:
            out[int(m.group(1), 16)] = m.group(2)
    return out


def referenced_addresses(s_path: Path) -> set[int]:
    """Every absolute address the function's disassembly materialises as data."""
    out: set[int] = set()
    text = s_path.read_text(encoding="utf-8", errors="replace")
    for m in LABEL.finditer(text):
        out.add(int(m.group(1)[2:], 16))
    for m in SYMBOL.finditer(text):
        name = m.group(1) or m.group(2)
        if re.fullmatch(r"D_[0-9A-Fa-f]{8}", name):
            out.add(int(name[2:], 16))
    return out


def classify(text: str) -> tuple[str, str] | None:
    m = TAGGED_PREFIX.match(text)
    if m and m.group("name").lower() not in LIBRARY_TAGS:
        return "verbatim", m.group("name")
    m = SELF_PREFIX.match(text)
    if m and m.group("name").lower() not in LIBRARY_TAGS:
        return "verbatim", m.group("name")
    if OBJECT.match(text):
        return "object", OBJECT.match(text).group("name")
    if BARE_IDENT.match(text):
        return "bare", BARE_IDENT.match(text).group("name")
    m = ASSERT.search(text)
    if m:
        return "assert", m.group("name")
    return None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--class", dest="classes", action="append",
                    choices=["verbatim", "object", "bare", "assert"])
    ap.add_argument("--json", type=Path)
    args = ap.parse_args()

    strings = load_strings()
    cands: dict[int, tuple[str, str]] = {}
    for addr, text in strings.items():
        c = classify(text)
        if c and (not args.classes or c[0] in args.classes):
            cands[addr] = c

    out: dict[str, list[dict]] = {}
    for s_path in sorted(ASM.glob("*.s")):
        stem = s_path.stem
        hits = sorted(referenced_addresses(s_path) & set(cands))
        for addr in hits:
            cls, name = cands[addr]
            out.setdefault(stem, []).append(
                {"cls": cls, "name": name, "string_addr": "0x%08X" % addr,
                 "text": strings[addr][:70]})

    if args.json:
        args.json.write_text(json.dumps(out, indent=1), encoding="utf-8")
        print("wrote %s" % args.json)

    for stem in sorted(out, key=lambda s: int(s, 16)):
        print("cod/%s  (0x%08X)" % (stem, ROM_BASE + int(stem, 16)))
        for r in out[stem]:
            print("    %-8s %-32s <- %s  %r"
                  % (r["cls"], r["name"], r["string_addr"], r["text"]))
    print("%d function(s) with a name candidate" % len(out))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
