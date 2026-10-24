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

# scratch draft against the container (no manifest edit, fast loop)
wsl -d Ubuntu -u root -- bash -lc "cd /mnt/c/.../ShadowDecomp && \
  python3 tools/xff_try.py KERNEL 000638 /tmp/draft.c --verbose"

# harvest the mechanically provable shapes (named + stripped functions)
wsl -d Ubuntu -u root -- bash -lc "cd /mnt/c/.../ShadowDecomp && \
  python3 tools/xff_shapes.py KERNEL --max-size 64 --jobs 4 --write"

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

## Status (Session 65)

| Metric | Value |
|---|---|
| Functions in the lane | **115** (`python3 tools/xffcheck.py KERNEL --all` → `115/115`) |
| Byte-exact `.text` | **1,612 B = 0.76 %** of the module |
| Remaining named functions | 825 (154,024 B) |
| Remaining stripped pool | 57,776 B (131 candidates from `tools/xff_inventory.py`) |

The 115 are: 45 leaf/wrapper functions from the earlier sessions (X005–X007),
**68 recovered by the shape harvester** (`tools/xff_shapes.py`: `ret-addr`,
`ret-load`, `ret-imm`, `ret-zero`, `empty`, `store-arg`, `store-arg-ret`,
`tail-call`), and 2 hand-written (`iosCdSetMode` 000638, `iosGetClock` 000858).

## What the 50 % target actually costs

Measured distribution of the 940 named functions (bytes per size bucket):

| Size bucket | Functions | Bytes | Cumulative bytes | % of `.text` |
|---|---:|---:|---:|---:|
| ≤ 32 B | 216 | 3,888 | 3,888 | 1.8 % |
| 33–64 B | 180 | 8,868 | 12,756 | 6.0 % |
| 65–128 B | 214 | 20,472 | 33,228 | 15.6 % |
| 129–256 B | 178 | 32,760 | 65,988 | 30.9 % |
| 257–512 B | 93 | 33,884 | 99,872 | 46.8 % |
| 513–1024 B | 42 | 30,300 | 130,172 | 61.0 % |
| > 1024 B | 17 | 25,464 | 155,636 | 72.9 % |

**Consequence:** 50 % of `.text` (106,706 B) is reached only after ~881
functions plus a dozen from the 513–1024 B bucket — i.e. **≈ 95 % of the named
functions (≈ 893 of 940)**. The target is not "half the work": the bytes are
concentrated in the medium and large bodies. The stripped pool is not needed at
all for 50 %.

Observed throughput so far: the shape harvester proves ~60 functions (≈1 KB) per
sweep; hand-written bodies cost one iteration loop each (000638 took 1 attempt,
000748 was still 13/23 words off after three struct/order variants). The boot-ELF
lane averaged ~16 functions per session over 64 sessions, so 50 % of `KERNEL.XFF`
is a **dozens-of-sessions** target, not a single-session one.

## Layout

```
overlays/kernel/
  c_sources.txt     <text offset stem> = <C source> [-G0] [size=...]
  src/<STEM>.c      one function per file, stem = offset in .text
```

Names in `src/*.c` come from the module's own `.symtab`. Data objects that have
no name in the table stay numbered (`D_kernel_bss_8050` = `.bss + 0x8050`) and are
marked `UNCONFIRMED` in the file header.
