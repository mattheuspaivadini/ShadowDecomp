# `KERNEL.XFF` decompilation lane

First overlay module of the project. Same rules as the boot ELF (`AGENTS.md`):
evidence over guesses, one commit per function, and a byte-exact gate — the gate
here is per function against the shipped module bytes.

## Why the gate is per function

`KERNEL.XFF` is a `xff2` container around a **relocatable** ELF image:
`.text` starts at vaddr 0, and every absolute address in it is patched by the
loader from a `.rel.text` entry (SHT_REL semantics: the addend sits in the
instruction). The module is never linked at build time, so there is no flat image
to hash. Instead each function is compiled with the pinned EE-GCC and compared
word-by-word with the original, masking every field covered by a relocation
(`tools/xffcheck.py`). This is the same masking `tools/matchcheck.py` applies to
the boot ELF.

## Commands

```sh
# list functions (C = already in this lane's c_sources.txt)
python tools/xffcheck.py KERNEL --list
python tools/xffcheck.py KERNEL --list --small 40

# annotated R5900 disassembly with the relocation targets
.venv/Scripts/python tools/xff_dis.py KERNEL 0005A8

# verify (must run inside WSL, like make check)
wsl -d Ubuntu -u root -- bash -lc "cd /mnt/c/.../ShadowDecomp && python3 tools/xffcheck.py KERNEL --all"
```

## Facts measured from the container

| Metric | Value |
|---|---|
| `.text` | 213,412 B (`0x341A4`) |
| `.rel.text` entries | 6,259 (HI16/LO16/26/32) |
| Symbols | 1,915 total; 940 `STT_FUNC` in `.text`, all `STB_GLOBAL` |
| Named function bytes | 155,636 B (73 %) |
| Unnamed code | 57,776 B in 530 gaps — **static functions were stripped**, the shipped `.symtab` keeps globals only |
| Ghidra EE export | 1,039 functions (`build/plan/ghidra_out/KERNEL/`) — it merges/undercounts the gap blocks, so it is a hint, not an inventory |
| Compiler | `-G0`: only 10 `$gp`-relative accesses in the whole module, every global uses `lui`/`addiu` |

## Status

44 functions, 476 B of `.text`, all byte-exact (`python3 tools/xffcheck.py KERNEL --all`
→ `44/44`). These are the leaf batch from the plan (`docs/plan/tasks.tsv` X005-X007)
plus three small routines with real logic (`0005A8`, `000620`, `0007D8`, `000AA0`).

Remaining: 896 named functions plus the unnamed static pool, i.e. ~99.8 % of the
module. The function inventory for the static pool still has to be produced
(Ghidra's 1,039 entries as a starting point, then a splat-style split).

## Layout

```
overlays/kernel/
  c_sources.txt     <text offset stem> = <C source> [-G0]
  src/<STEM>.c      one function per file, stem = offset in .text
```

Names in `src/*.c` come from the module's own `.symtab`. Data objects that have
no name in the table stay numbered (`D_kernel_0000B8` = `.data + 0xB8`) and are
marked `UNCONFIRMED` in the file header.
