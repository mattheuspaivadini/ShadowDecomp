# Shadow of the Colossus (USA, PS2) — Matching Decompilation

A reproducible, byte-exact matching decompilation of the main executable of
**Shadow of the Colossus (NTSC-U, PlayStation 2)**, `SCUS_974.72`.

Success means rebuilding the ELF from our assembly and C sources and obtaining a
**byte-exact hash match** with the original. The project does **not** contain any
copyrighted game material: you must supply your own legally owned copy of the disc.

---

## Current status

| Metric | Value |
|--------|-------|
| Flat load image | **237,952 bytes**, SHA-1 `6f853f64…` — **HASH MATCH** |
| ELF container | `SCUS_974.72` (242,940 bytes, SHA-1 `b715b349…`) — **byte-identical** |
| Functions in the image | 1,042 real functions (+ 2 raw `textbin` regions) |
| Functions matched from C | **1,016 / 1,042** (97.50 %) |
| Matched code bytes | **187,892 / 203,692** `.text` bytes (**92.24 %**) |
| Near-miss attempts | 12 drafts in `src/non_matching/` (diff lines range from 2 to 114) |
| Named symbols | ~55 evidence-derived `.text` names, plus 840 SDK names imported from `KERNEL.XFF` |
| Remaining real pool | 13 (12 near-miss + 1 untouched) |

Every matched function is gated by the image hash, so a change that breaks any
function is caught immediately.

### Phases

| # | Phase | Status |
|---|-------|--------|
| 1 | Extract the ISO (pure-Python ISO9660 reader) | Done |
| 2 | Analyze the ELF (sections, segments, entry, strings) | Done |
| 3 | Pin the compiler (EE-GCC revision and flags) | Done — `-O2 -g2 -G8`, mixed generations per translation unit |
| 4 | Split and rebuild (per-function assembly, byte-exact link, container) | Done |
| 5 | Name functions and data from evidence | In progress |
| 6 | Decompile functions to C, byte-exact | In progress (902 / 1,042) |

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
- **Hand-written assembly:** 13 functions remain `asm-permanent` in the ledger: the crt0
  `entry` (128-bit `sq` .bss clear, raw syscalls), three kernel exception vectors (full
  register saves with `mfhi1`/`mfsa`), and 9 MMI string routines. The syscall-stub table and
  the `$gp`/Status-register functions once classed this way turned out to be C with inline asm.
  The MMI routines look like Newlib C with inline asm built by ee-gcc 2.9-ee-990721
  (`tools/cc/make_hybrid_990721.sh`); strlen, memcpy and memset are archived as near-misses.

---

## Repository layout

```
asm/            Per-function split assembly (1,042 files under asm/cod/, plus data)
src/cod/        Matched C sources (byte-exact)
src/non_matching/  Near-miss attempts, each with a STATUS note
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

- The REA MCP toolset cannot analyze R5900 ELFs on Windows (its native lane is PE-only). Analysis uses splat, rabbitizer, Ghidra with the EE extension, and local scripts.
- Overlay modules (`.XFF`: `KERNEL`, `MANAGER`, `GAMECORE`) are split but mostly not decompiled.
- The remaining near-miss drafts are mostly register-allocation, scheduler or branch-layout differences. Some residual classes have no compiler flag that fixes them yet.
- The `origin` remote points to `github.com/mattheuspaivadini/ShadowDecomp`; the ISO and the game-derived files are never pushed.

---

## Legal

This project contains only tooling, configuration, notes, assembly and C source written for
interoperability and preservation. It does not distribute any game data. Use it only with a
copy of the game that you own.
