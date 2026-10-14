#!/usr/bin/env python3
"""Move un-manifested src/cod/*.c attempts into src/non_matching/ with a STATUS note.

The original .s stays in the build; only the failed C attempt is relocated.
"""
from __future__ import annotations

import pathlib

root = pathlib.Path(__file__).resolve().parent.parent
cod = root / "src" / "cod"
nm = root / "src" / "non_matching"

reason = {
    "002790": "ee-gcc software-pipelines the 256-entry table scan (the value is "
              "loaded one iteration ahead and the index is saved before the "
              "increment). Plain for/while/do-while + break yields a bounds-first "
              "loop; both revisions and -g0 tried.",
    "0027E0": "same pipelined table-scan family as func_00102790 (on D_0013BB90).",
    "002830": "same pipelined table-scan family (first zero entry).",
    "002970": "same pipelined table-scan family (search + clear).",
    "00FC40": "loop peel + branch-likely (beql/bnel) + movz exit; GCC does not "
              "rotate/peel our loop the same way.",
    "007C70": "only the final store placement differs: the original puts `sb` in "
              "the `jr ra` delay slot; ours emits `sb` before `jr ra`. Tested "
              "-g0/-g2 and both revisions.",
    "010EF0": "block layout: the original branches `bgez` to the normal path with "
              "the error return inline; ours inlines the normal path and branches "
              "to the error.",
    "011700": "loop rotation / nop padding of the free-list init differs.",
    "011288": "64-bit guarded record access; register allocation and `ld` "
              "scheduling differ.",
    "011C50": "table lookup; the `bgezl` layout and register roles differ.",
    "012C78": "negative-index branch; the masked-index/constant registers differ "
              "(v0/a1 in the original vs a2/v1 in ours).",
    "013098": "arena step; the load order of field00/field08 differs.",
    "013368": "64-bit split store; register allocation differs.",
    "017A00": "if-chain: our chain emits `bnel` skips where the original emits "
              "`beq` to shared case blocks; a `switch` becomes a range check + "
              "jump table.",
    "01BAE8": "strchr-with-offset; load order and register roles differ.",
    "01BBB8": "string validator; the `lbu`+sign-extend spelling and delay-slot "
              "scheduling differ.",
    "01C138": "record init; the original's several uncoalesced base-pointer "
              "copies are not reproduced.",
    "01C198": "same record-init family as func_0011C138.",
    "020D10": "record key search; only the order of `+0xD0` vs the base add "
              "differs (3 instructions).",
    "027048": "float decompose; `mant << 7` placement and register roles differ.",
    "011F90": "scheduling: the original materialises the constant before the "
              "epilogue `ld ra`; ours loads ra first.",
    "0120D0": "same scheduling case as func_00111F90.",
}

man: set[str] = set()
for ln in (root / "config" / "c_sources.txt").read_text().splitlines():
    ln = ln.split("#", 1)[0].strip()
    if "=" in ln:
        man.add(ln.split("=")[0].strip())

moved = []
for p in sorted(cod.glob("*.c")):
    stem = p.stem
    if stem in man:
        continue
    why = reason.get(stem, "shape/allocation difference; see docs/progress.md.")
    note = (f"/* STATUS (Session 4, 2026-10-14): NON_MATCHING. {why}\n"
            f" * The original .s stays in the build (asm/cod/{stem}.s); this C\n"
            f" * attempt is kept for the record. */\n")
    dst = nm / p.name
    dst.write_text(note + p.read_text(encoding="utf-8"), encoding="utf-8")
    p.unlink()
    moved.append(stem)

print(f"moved {len(moved)}: {' '.join(moved)}")
