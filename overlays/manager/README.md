# `MANAGER.XFF` decompilation lane

Second overlay module, same rules and gate as `KERNEL.XFF` (`AGENTS.md`):
evidence over guesses, one commit per function, byte-exact per function against
the shipped module bytes.

## Gate

`MANAGER.XFF` is a `xff2` container around a **relocatable** EE image (`.text`
at vaddr 0, 19,051 `.rel.text` entries), so there is no flat image to hash. Each
function is compiled with the pinned EE-GCC and compared word-by-word with the
container, masking every field covered by a relocation (`tools/xffcheck.py`).

```sh
# list functions (C = already in this lane's c_sources.txt)
python tools/xffcheck.py MANAGER --list
python tools/xffcheck.py MANAGER --list --small 40

# annotated R5900 disassembly with relocation targets
.venv/Scripts/python tools/xff_dis.py MANAGER 003E88

# verify (inside WSL, like make check)
wsl -d Ubuntu -u root -- bash -lc "cd <repo> && python3 tools/xffcheck.py MANAGER --all"
```

## Facts measured from the container

| Metric | Value |
|---|---|
| `.text` | 981,944 B (`0xEFBB8`) |
| `.vutext` (VU1 microcode) | 110,192 B (`0x1AE70`) — separate section, not C |
| `.data` / `.rodata` / `.bss` | 41,408 B / 27,832 B / 94,544 B |
| `.rel.text` entries | 19,051 |
| Symbols | 2,818 total (433 imports); 2,277 `STT_FUNC` in `.text`, **all `STB_GLOBAL`** |
| Named function bytes | 574,888 B (58.5 %) |
| Unnamed code | **407,056 B in 1,291 gaps (41.4 %)** — statics were stripped as in `KERNEL.XFF` |
| Ghidra EE export | 3,046 functions (`build/plan/ghidra_out/MANAGER/`) |
| Compiler | `-G0`: 7 `$gp`-relative accesses in 982 KB |
| DVP | `.DVP.ovlytab` + 60 `.DVP.overlay.*` sections (VU1 overlay management, data) |

## Status

120 functions, 1,032 B of `.text`, all byte-exact (`--all` → `120/120`):

- **114 of the 8-byte functions** — the complete set at that size: empty bodies,
  one-field accessors (int/byte/short/float), one-field setters, constant
  returns, identity, and one `sub.s` helper (`0058C8`).
- **6 with real bodies** (20 B each): `003E88` tail call, `009008` float
  accumulator (`f(+0xC) = f(+0x14) + f(+0x18)`), `009248` four-float setter
  (sched2 rotates the stores, so the source keeps ascending order), `01E298`
  indexed record load (32-byte stride, forced by a record struct), `085980`
  null-safe accessor, `0CC8E8` two-way link relocation guarded by `bnel`.

Remaining: 2,157 named functions plus the 407 KB static pool. The static pool
needs an inventory (Ghidra's 3,046 entries as a starting point) before it can be
planned — it is 20× larger than `KERNEL.XFF`'s.

## Layout

```
overlays/manager/
  c_sources.txt     <text offset stem> = <C source> [-G0]
  src/<STEM>.c      one function per file, stem = offset in .text
```
