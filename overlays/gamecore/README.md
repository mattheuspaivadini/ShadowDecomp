# `GAMECORE.XFF` decompilation lane

Third (and largest) overlay module, same rules and gate as `KERNEL.XFF` and
`MANAGER.XFF` (`AGENTS.md`): evidence over guesses, one commit per function,
byte-exact per function against the shipped module bytes.

## Gate

`GAMECORE.XFF` is a `xff2` container around a **relocatable** EE image (`.text`
at vaddr 0, 40,027 `.rel.text` entries in two tables), so there is no flat image
to hash. Each function is compiled with the pinned EE-GCC and compared
word-by-word with the container, masking every field covered by a relocation
(`tools/xffcheck.py`).

```sh
python tools/xffcheck.py GAMECORE --list
python tools/xffcheck.py GAMECORE --list --small 40
.venv/Scripts/python tools/xff_dis.py GAMECORE 007318

# verify (inside WSL, like make check)
wsl -d Ubuntu -u root -- bash -lc "cd <repo> && python3 tools/xffcheck.py GAMECORE --all"
```

## Facts measured from the container

| Metric | Value |
|---|---|
| `.text` | 1,226,112 B (`0x12B580`) |
| `.data` / `.rodata` / `.bss` | 8,260 B / 22,416 B / 139,336 B |
| `.rel.text` entries | 40,027 (tables of 19,683 + 20,344) |
| Symbols | 4,646 total (1,849 imports); 2,755 `STT_FUNC` in `.text`, **all `STB_GLOBAL`** |
| Named function bytes | 544,916 B (44.4 %) |
| Unnamed code | **681,196 B in 1,536 gaps (55.6 %)** — statics were stripped, as in the other two modules |
| Ghidra EE export | 4,568 functions (`build/plan/ghidra_out/GAMECORE/`) |
| Compiler | `-G0` (58 `$gp`-relative accesses in 1.2 MB); at least one TU also uses `-fno-optimize-sibling-calls` (see below) |

## Status

242 functions, 2,060 B of `.text`, all byte-exact (`--all` → `242/242`):

- **235 of the 8-byte functions** — the complete set at that size: empty bodies,
  one-field accessors (int/byte/short/float), one-field setters, constant and
  zero returns, `x != 0` (`sltu`), pointer arithmetic, 64-bit zero stores.
- **7 with real bodies** (24-28 B): `007318` non-sibling call, `00B430` endless
  `scrRun()` loop (the branch targets the `jal`), `00BE98` store + sibling call
  into an unnamed static, `0140E8` / `01E590` constant-argument wrappers,
  `02C020` second-argument wrapper, `02E1C8` load + `scriptIntrSignal`.

**Levers:** the same as `MANAGER.XFF` (float arguments in `$f12-$f15` in order,
`-G0`), plus one new one: `007318` keeps a frame and a real `jal` + `jr` where
its neighbours use a sibling `j`, which makes that translation unit
`-fno-optimize-sibling-calls` (recorded per stem in `c_sources.txt`).

Remaining: 2,513 named functions plus **681 KB of stripped static code** — the
largest unknown of all three modules (about 1.7× `MANAGER.XFF`'s pool).
