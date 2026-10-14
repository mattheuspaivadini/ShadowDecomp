#!/usr/bin/env python3
"""Post-process a splat config so `.text` is emitted as one `.s` file per function.

splat has no built-in "one file per function" mode; the idiomatic layout is many
`asm` subsegments under the `code` parent, each producing one `.s`. This tool
takes the base config produced by `tools/splat_ps2_config.py` (where `.text` is a
single `[0x000000, asm, cod/000000]` subsegment) and replaces that line with:

  * a 16-byte `data` subsegment for the `.text` header (verified: two 32-bit
    pointers `0x00102CF8` and `0x00100C80` followed by two zero words, then the
    entry point at `0x00100010`), and
  * one `asm` subsegment per function label found in the previous split's `.s`.

Function start addresses are taken from splat's own output
(`asm/cod/000000.s`): every `glabel func_XXXXXXXX` carries its VRAM address, and
named symbols (e.g. `entry`) are resolved through `config/symbol_addrs.txt`.

Pipeline (run with the project venv python):

    .venv\\Scripts\\python.exe tools/splat_ps2_config.py extracted/SCUS_974.72 \
        build/SCUS_974.72.rom config/SCUS_974.72.yaml
    .venv\\Scripts\\python.exe tools/gen_function_splits.py \
        config/SCUS_974.72.yaml asm/cod/000000.s config/symbol_addrs.txt \
        config/SCUS_974.72.yaml
    .venv\\Scripts\\splat.exe split config/SCUS_974.72.yaml
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

TEXT_SEGMENT_VRAM = 0x00100000
TEXT_HEADER_SIZE = 0x10  # two pointers + two zero words before `entry`
TEXT_ROM_START = 0x000000
TEXT_ROM_END = 0x031BAC  # from the ELF section map (.text size)

TEXT_SUBSEG_LINE = re.compile(
    r"^(\s*-\s*\[)0x0*0*0000,\s*asm,\s*[^\]]*\](\s*#\s*\.text\s*)$"
)
GLABEL = re.compile(r"^glabel\s+(\S+)\s*$")
SYM_ASSIGN = re.compile(r"^\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def parse_symbol_addrs(path: Path) -> dict[str, int]:
    """name -> vram for every `name = 0xADDR;` line."""
    out: dict[str, int] = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        m = SYM_ASSIGN.match(line.strip())
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


def parse_function_starts(asm_s: Path, symbols: dict[str, int]) -> list[tuple[int, str]]:
    """Return sorted (vram, label) for every glabel in the single-file .s."""
    funcs: list[tuple[int, str]] = []
    for line in asm_s.read_text(encoding="utf-8", errors="replace").splitlines():
        m = GLABEL.match(line)
        if not m:
            continue
        name = m.group(1)
        if name.startswith("func_") and re.fullmatch(r"func_[0-9A-Fa-f]{8}", name):
            vram = int(name[5:], 16)
        elif name in symbols:
            vram = symbols[name]
        else:
            raise SystemExit(f"cannot resolve address for label {name!r}")
        funcs.append((vram, name))
    funcs.sort()
    return funcs


def build_text_block(funcs: list[tuple[int, str]]) -> str:
    # `textbin` emits raw bytes into `.text` (as an `.incbin`), which is where the
    # 2-pointer + 2-zero-word header physically lives (0x00100000..0x0010000F).
    # A `data` subsegment would wrongly land in the `.data` output section.
    lines: list[str] = [
        f"      - [0x{TEXT_ROM_START:06X}, textbin, cod/000000]"
        " # .text header (2 pointers + 2 zero words)"
    ]
    for vram, name in funcs:
        rom = vram - TEXT_SEGMENT_VRAM
        if rom >= TEXT_ROM_END:
            break
        lines.append(f"      - [0x{rom:06X}, asm, cod/{rom:06X}] # {name}")
    return "\n".join(lines) + "\n"


def main(config_in: str, asm_s: str, symbol_addrs: str, config_out: str) -> None:
    symbols = parse_symbol_addrs(Path(symbol_addrs))
    funcs = parse_function_starts(Path(asm_s), symbols)
    # Drop anything at or before the header (e.g. the bogus func_00100000).
    funcs = [(v, n) for (v, n) in funcs if v >= TEXT_SEGMENT_VRAM + TEXT_HEADER_SIZE]
    funcs.sort()
    if not funcs:
        raise SystemExit("no function labels found in the .s file")

    block = build_text_block(funcs)
    text_in = Path(config_in).read_text(encoding="utf-8").splitlines(keepends=True)

    replaced = False
    out_lines: list[str] = []
    for line in text_in:
        if TEXT_SUBSEG_LINE.match(line.rstrip("\n")):
            if replaced:
                raise SystemExit("more than one `.text` subsegment line found")
            out_lines.append(block)
            replaced = True
        else:
            out_lines.append(line)
    if not replaced:
        raise SystemExit("could not find the single `.text` asm subsegment line")

    Path(config_out).write_text("".join(out_lines), encoding="utf-8", newline="\n")
    print(f"wrote {config_out}")
    print(f"  {len(funcs)} functions -> 1 data + {len(funcs)} asm subsegments")


if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    main(*sys.argv[1:])
