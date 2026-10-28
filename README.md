# Shadow of the Colossus (USA, PS2) — Matching Decompilation

A reproducible, byte-exact matching decompilation of the main executable of
**Shadow of the Colossus (NTSC-U, PlayStation 2)**, `SCUS_974.72`.

Success means rebuilding the ELF from our assembly and C sources and obtaining a
**byte-exact hash match** with the original. The project does **not** contain any
copyrighted game material: you must supply your own legally owned copy of the disc.

---

## Current status

### Main executable `SCUS_974.72`

| Metric | Value |
|--------|-------|
| Flat load image | **237,952 bytes**, SHA-1 `6f853f64…` — **HASH MATCH** |
| ELF container | `SCUS_974.72` (242,940 bytes, SHA-1 `b715b349…`) — **byte-identical** |
| Code bytes | **203,692** `.text` bytes, all attributed (no gaps, no overlaps) |
| Functions in the image | 1,042 real functions (+ 2 raw `textbin` regions) |
| Functions compiled from C | **1,037 / 1,042** (99.52 %) — of which **12 are asm transcriptions, not recovered C** |
| Functions recovered as C | **1,025 / 1,042** (98.37 %) |
| Recovered-C bytes | **190,188 / 203,692** `.text` bytes (**93.37 %**) |
| Remaining real function | 1 untouched (`func_00107FF8`, the SCE printf core, 3,352 B) |
| Hand-written assembly | 4 functions (crt0 `entry` + 3 exception vectors), 1,040 B |
| Named `.text` labels | 834 / 1,044; 210 automatic (18 of them have an authoritative `KERNEL.XFF` name) |
| Near-miss drafts | 12 readable and codegen-tuned attempts in `src/non_matching/` (plus `archive/`) |

Every matched function is gated by the image hash, so a change that breaks any
function is caught immediately.

### Overlay modules (`.XFF`)

| Module | `.text` | Decompiled from C | Gate |
|---|---:|---:|---|
| `KERNEL.XFF` | 213,412 B (940 named + 57,776 B unnamed static code) | **788 functions, 79,064 B** (37.0 %; 737 / 940 named + 51 static) | `python3 tools/xffcheck.py KERNEL --all` → 788/788 byte-exact, reloc-masked |
| `MANAGER.XFF` | 981,944 B (2,277 named + 407,056 B unnamed static code) + 110,192 B VU1 | **127 functions, 1,176 B** (leaf batch + 7 static) | `python3 tools/xffcheck.py MANAGER --all` → 127/127 byte-exact, reloc-masked |
| `GAMECORE.XFF` | 1,226,112 B (2,755 named + 681,196 B unnamed static code) | **262 functions, 2,512 B** (leaf batch + 20 static) | `python3 tools/xffcheck.py GAMECORE --all` → 262/262 byte-exact, reloc-masked |
| IOP (`SG2IOPM1.IRX`, `PL2303.IRX`) | 20,448 B | 0 | inventoried |

The overlays are relocatable images (no flat hash), so their gate is per-function:
compile with the pinned EE-GCC and compare against the container bytes with the
relocation fields masked (`overlays/kernel/README.md`).

### Phases

| # | Phase | Status |
|---|-------|--------|
| 1 | Extract the ISO (pure-Python ISO9660 reader) | Done |
| 2 | Analyze the ELF (sections, segments, entry, strings) | Done |
| 3 | Pin the compiler (EE-GCC revision and flags) | Done — `-O2 -g2 -G8`, mixed generations per translation unit |
| 4 | Split and rebuild (per-function assembly, byte-exact link, container) | Done |
| 5 | Name functions and data from evidence | In progress (210 automatic labels left) |
| 6 | Decompile functions to C, byte-exact | In progress — main ELF 1,025 / 1,042; `KERNEL.XFF` 737 / 940 named |
| 7 | Decompile the `.XFF` overlays | In progress: `KERNEL.XFF` 788, `MANAGER.XFF` 127, `GAMECORE.XFF` 262 functions (1,177 total, all byte-exact) |

## What is still missing for "100 % decompiled"

The executable's **bytes are complete** (hash-matched, container-identical). The
*source* is not. In ascending order of effort:

1. **`func_00107FF8` — 3,352 B (1.65 % of `.text`).** The SCE libc printf core: an
   89-entry format switch (`jtbl_00137D40`), 22 callback `jalr`s, frame `0x120`.
   All six callers (`sceVsnprintf`, `sceSnprintf`, `sceVprintf`, `scePrintf`,
   `kprintf`, `008DB8`) and all seven callees are already matched, so it is a
   pure reconstruction job (comparable engines already recovered: `_vfprintf_r`
   5,744 B, `_dtoa_r` 4,712 B, `__svfscanf` 3,216 B).
2. **12 asm transcriptions — 9,092 B (4.46 %).** `000590 0059D8 00A388 012E80
   0141B8 0150B0 017AB0 01CEB0 01D9E8 028E6C 029200 0293B8` are byte-exact
   `__asm__` copies of their `.s`; the readable C is in `src/non_matching/` but
   still differs by one scheduler/register-allocation decision. Needs a compiler
   build with the right `reorg`/allocation behaviour, or an explicit
   "C-equivalent, not byte-exact" status.
3. **Hand-written assembly — 1,040 B (0.51 %), legitimately not C.** `entry` (crt0:
   `$gp`/`$sp` from syscalls, `sq` `.bss` clear, `EI`) and the three kernel
   exception vectors (`00F7C0`, `00F900`, `00FA00`: `$k0`/`$at` saves, `mfhi1`,
   `mfsa`, `mtc0`, `eret`). Plus 20 B of `textbin` (the `.text` header and a 4-byte
   boundary artifact at `0x113074`).
4. **Names — 210 of 1,044 `.text` labels are still `func_XXXXXXXX` (46,680 B).**
   18 have an authoritative `KERNEL.XFF` name ready to apply (`abort`, `atexit`,
   `memcpy`, `strlen`, `printf`, `vfprintf`, …); the other 192 are file-scope
   statics that need string/caller evidence.
5. **Data — 34,020 B recovered as bytes, not as source.** `.data` 17,612 B (265
   labels), `.rodata` 15,448 B (366 labels, 483 strings, 106 relocated jump
   tables), `.sdata` 896 B, plus 197,032 B of `.bss`. Only a handful of objects have
   a declared type (`include/symbols.h`) or a documented layout (`docs/structs.md`);
   the rest are labelled word dumps emitted by splat.
6. **The rest of the game — 2,531,660 B of EE code + 20,448 B of IOP code, ~3 %
   decompiled.** The boot ELF is only **7.4 %** of the executable code on the disc:

   | Binary | `.text` | Status |
   |---|---:|---|
   | `KERNEL.XFF` | 213,412 B | 788 functions recovered (79,064 B, 37.0 %) |
   | `MANAGER.XFF` | 981,944 B + 110,192 B VU1 | 127 functions recovered (1,176 B) |
   | `GAMECORE.XFF` | 1,226,112 B | 262 functions recovered (2,512 B) |
   | `SG2IOPM1.IRX`, `PL2303.IRX` | 20,448 B | 0 % |

   Unlike the boot ELF, the `.XFF` symbol tables keep **globals only**, so 47 % of
   the overlay code is unnamed static functions (1,146,028 B). Those gaps now have
   an evidence-based inventory (`tools/xff_inventory.py`): **1,455 candidate
   functions / 873 KB**, built from Ghidra starts plus `jal` targets. 78 of them
   are already decompiled byte-exactly (28 by the template pass `tools/xff_autotry.py`,
   the rest by hand; 51 are in `KERNEL.XFF`); the other 1,377 are real functions
   (frames, loops, calls) and need the normal per-function loop. Details in `docs/xff-statics.md` (local notes).

So: **bytes 100 %, main-executable C 93.37 %, whole game ≈ 9.9 %** (272,940 of
2,755,800 B of code recovered as C). Everything above
is tracked with evidence in `docs/ledger.json` (main ELF), `overlays/*/c_sources.txt`
(overlay lanes) and the local notes (`docs/completeness-audit.md`, not versioned).


---

## Key findings

- **Target CPU:** MIPS R5900 (Emotion Engine), little-endian, with 128-bit MMI and VU0 macro-mode instructions.
- **Compiler:** the original is built by **more than one EE-GCC generation**. No single
  revision reproduces every function; each translation unit records which compiler it
  matches (`cc=` in `config/c_sources.txt`):
  - `ee-gcc2.96` (`2.96-ee-001003-1`) — default
  - `ee-gcc2.9-991111-01` — `cc=29`
  - `2.95.3-136` (Windows build, run under wine) — `cc=wine:…`
- **Flags:** `-O2 -g2 -G8`, with per-translation-unit overrides (`-g0`, `-G0`,
  `-fno-optimize-sibling-calls`, `-fno-schedule-insns`, `-fno-strict-aliasing`,
  `-fno-delayed-branch`). `-O1` and `-Os` are ruled out; `-O2` and `-O3` cannot be told apart.
- **Type model:** in this build `int` and `void *` are 4 bytes, while `long`, `unsigned long`
  and `long long` are 8 bytes.
- **Library provenance:** several libraries in the image are recognizable revisions:
  Newlib 1.9.0 (stdio, malloc, strtol, mprec, reent), GCC 2.95.3 `libgcc2`, and SCE SDK
  template families (SIF-RPC stdio, `sceMc2*` async, `sceVif1Pk*`, `sceDma*`).
- **Hand-written assembly:** 4 functions remain `asm-permanent` in the ledger: the crt0
  `entry` (128-bit `sq` .bss clear, raw syscalls that set `$gp`/`$sp`) and three kernel
  exception vectors (`$k0`/`$at` full register saves with `mfhi1`/`mfsa`, `mtc0`, `eret`).
  The syscall-stub table, the `$gp`/Status-register functions and the MMI string routines once
  classed this way turned out to be C with inline asm. The MMI routines are Newlib C with
  inline asm built by ee-gcc 2.9-ee-990721 + the 991111 assembler
  (`tools/cc/make_hybrid_990721.sh`); 9 of 12 match from recovered C, and
  strcmp/strncmp/strncpy are byte-exact assembly transcriptions.

---

## Repository layout

```
asm/            Per-function split assembly (1,042 files under asm/cod/, plus data)
src/cod/        Matched C sources (byte-exact)
src/non_matching/  Near-miss attempts, each with a STATUS note
overlays/       .XFF overlay decompilation lanes (kernel/, manager/, gamecore/: src/, c_sources.txt, README)
include/        Headers, symbol macros, SDK stubs
config/         Splat config, symbol_addrs.txt (single source of truth for names),
                c_sources.txt (per-TU compiler selection), compiler flags
tools/          Build, verification, permuter, analysis and reporting scripts
manifest/       File list with SHA-1/MD5 of the ISO contents (no game data)
build/          Build outputs (ignored)
extracted/      Files extracted from the ISO (ignored)
```

Local working notes (session logs, plans, decisions and the archive) are kept on disk
but are **not versioned**; see `.gitignore`.

---

## Building

### Requirements

- The original ISO, `Shadow of the Colossus (USA).iso`, placed at the repository root
  (it is never modified and never committed).
- Windows 11 with **WSL2 (Ubuntu)** for the Linux build environment.
- Inside WSL: `binutils-mips-linux-gnu` (2.45 or compatible), `python3`, `make`, `ninja`.
- The EE-GCC compilers. Fetch them with `tools/cc/fetch_eegcc.sh`; they are
  gitignored under `tools/cc/*/`. Revisions needing `libc6:i386` or `wine` are noted in the script.
- Python: `splat64` (`splat64[mips]` 0.50.1), in a virtual environment at `.venv/`.
- Optional: `objdiff-cli` (3.8.2) for side-by-side function diffs.

### Commands

```sh
# Extract the ISO into extracted/ and rebuild the manifest (never modifies the ISO)
python tools/extract_iso.py "Shadow of the Colossus (USA).iso" extracted manifest/files.txt

# Full build: assemble + compile + link, gated on the flat-image SHA-1
make check            # or: python3 tools/build.py --jobs 8   (inside WSL)

# Verify every C function byte-for-byte (fast gate, ~20 s)
python build/s10/verify_fast.py          # or: make fast   (runs it inside WSL)

# Full slow verification (~1.5 h); not for routine gating
make verify

# Rebuild the ELF container and compare it with the original
make container
make elf-diff

# Progress summary
make report

# Diff one function against the original
make diff F=func_001128C0

# Overlay lanes (KERNEL.XFF / MANAGER.XFF / GAMECORE.XFF): list and verify
python3 tools/xffcheck.py KERNEL --list
python3 tools/xffcheck.py KERNEL --all      # inside WSL, like make check
python3 tools/xffcheck.py MANAGER --all
python3 tools/xffcheck.py GAMECORE --all

# .XFF static (unnamed) code: inventory and mechanical first pass
python3 tools/xff_inventory.py           # counts + candidate functions per module
python3 tools/xff_autotry.py KERNEL --all --max-size 200   # template pass (WSL)
```

Run `make help` for the full target list.

---

## Working on a function

1. Read the target assembly in `asm/cod/<STEM>.s` and its callers and callees.
2. Write C in `src/cod/<STEM>.c` with confirmed types. Add structs and symbols to `include/` only with evidence.
3. Register the file in `config/c_sources.txt` with the correct `cc=` selector.
4. Compare the output with the original. Adjust variable order, types, loop forms and temporaries until the bytes match.
5. If it does not match after reasonable attempts, archive the draft to `src/non_matching/` with a `STATUS:` header.
6. Confirm `make check` still prints **HASH MATCH**.

---

## Conventions

- **Evidence over guesses.** Names come only from evidence (strings, object names, call
  graphs, SDK identities). Anything uncertain is marked `// UNCONFIRMED: <reason>`.
- **Auto names** stay `func_XXXXXX` / `D_XXXXXX` until evidence exists.
- **Commits:** one function per commit: `decomp: <function_name> (<stem>) matching`,
  `non-matching: <function_name> (<stem>) <old score> -> <new score>`, or `phaseN: ...`.
- **Never commit** the ISO, extracted game files, original ELF/IRX/XFF binaries, or build outputs.

---

## Limitations and open issues

- The REA MCP toolset cannot analyze R5900 ELFs on Windows (its native lane is PE-only). Analysis uses splat, rabbitizer, Ghidra with the EE extension, and local scripts; the Ghidra-EE export is bridged into REA as an evidence bundle (`tools/rea_ghidra_evidence.mjs`).
- Two `KERNEL.XFF` lane entries (019BB8, 019E18) add `-fno-delete-null-pointer-checks` to the module flags `-G0 -fno-strict-aliasing`; the original keeps NULL tests after dereferences there.
- All three overlays have decompilation lanes: `KERNEL.XFF` 788, `MANAGER.XFF` 127, `GAMECORE.XFF` 262 functions, all byte-exact (`overlays/`). Their symbol tables keep globals only, so 47 % of the overlay code (1,146,028 B) is unnamed static functions; the gaps now have an evidence-based inventory of 1,455 candidates / 873 KB (`tools/xff_inventory.py`), of which 78 are decompiled (28 mechanically with `tools/xff_autotry.py`, the rest by hand) and 1,377 still need per-function work. `KERNEL.XFF` leftovers include hand-written VU0 statics (kept as asm), soft-float double code and a few parked near misses (see `CONTEXT.md`). `MANAGER.XFF` also carries 110,192 B of VU1 microcode (`.vutext`), which is not C.
- The twelve former near-miss drafts were promoted as byte-exact **assembly transcriptions**; their recovered-C forms remain in `src/non_matching/` and differ only in register allocation, scheduling or branch layout. The single remaining undecompiled function is `func_00107FF8` (SCE printf core).
- The `origin` remote points to `github.com/mattheuspaivadini/ShadowDecomp`; the ISO and the game-derived files are never pushed.

---

## Legal

This project contains only tooling, configuration, notes, assembly and C source written for
interoperability and preservation. It does not distribute any game data. Use it only with a
copy of the game that you own.
