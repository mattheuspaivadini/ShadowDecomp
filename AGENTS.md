# AGENTS.md — Shadow of the Colossus (USA, PS2) Decompilation

> Read this file at the start of EVERY session. Update the "Progress" and "Session log" sections before ending a session.

## 1. Project goal

Build a reproducible matching decompilation of the main executable of **Shadow of the Colossus (NTSC-U, PlayStation 2)** from the owner's legally owned copy.

- Target CPU: MIPS R5900 (Emotion Engine), little-endian, with 128-bit MMI and VU0 macro-mode (COP2) instructions.
- Success = rebuilding the ELF from our assembly + C and obtaining a **byte-exact hash match** with the original.
- Likely compiler: EE-GCC 2.96 (`-O2`, PS2 SDK flags). This is a hypothesis; confirm it by experiment (see section 6).

## 2. Hard rules

1. **Never modify the original ISO.** Work only on copies in `extracted/` and `build/`.
2. **No copyrighted material in git**: ISO, extracted game data, original ELF/IRX binaries, and generated build outputs are all in `.gitignore`. The repo contains only tooling, configs, hashes, notes, ASM and C source.
3. **Evidence over guesses.** Never invent function names, struct layouts, or behavior. Mark guesses with `// UNCONFIRMED: <reason>`.
4. **Small, verifiable steps.** After each step, verify (hash, diff, build) before moving on.
5. **Commit after each completed phase** with a clear message.
6. **If a step fails**: diagnose, try at least two alternative approaches, then report the blocker with the exact error output.
7. **Do not ask for confirmation between phases** unless a decision is irreversible. Record choices in `docs/decisions.md`.
8. **Long commands** (full analysis, big builds): run in the background and poll. Keep foreground shell commands short.
9. Respond to the user in Portuguese; write code, comments, commits, and docs in English.

## 3. Directory layout

```
SHADOWDECOMP/        # THIS directory is the project root; the game ISO sits here (read-only, never commit)
extracted/           # files extracted from the ISO (gitignored)
build/               # build outputs (gitignored)
config/              # splat YAML, symbol_addrs.txt, compiler flags
asm/                 # split assembly per segment/function
src/                 # decompiled C (one file per logical unit)
include/             # headers, structs, SDK stubs
tools/               # scripts, wrappers, diff helpers
docs/                # decisions.md, compiler.md, structs.md, progress notes
manifest/            # file list + SHA-1/MD5 hashes (commit this)
AGENTS.md            # this file
```

Create missing directories as needed. Keep this layout in sync with reality.

## 4. Tooling

Fill in the table during DISCOVERY and keep it current.

| Tool | Purpose | Status / path |
|------|---------|---------------|
| REA (Reverse Engineering Anything) `rea-agents@6.4.0` | RE toolset + MCP server | Installed; **MCP attached** (170 tools). Deep-analysis lane unusable for PS2 on Windows (PE-only gate) — use for artifact inventory + evidence bundles only. See `docs/rea.md` |
| Ghidra 12.1.4 + `ghidra-emotionengine-reloaded` v2.1.38 | Native analysis (headless) | `C:\Users\Matheus\ghidra\ghidra_12.1.4_PUBLIC`; EE extension language `r5900:LE:32:default` decodes **100 %** of `.text`. See `docs/rea.md` |
| splat64 | Split ELF into asm/data | **0.50.1 installed** in `.venv` (+ spimdisasm 1.42.4, rabbitizer 1.16.2). **Per-function split**: 1037 `.s` under `asm/cod/` — see `docs/splat.md` |
| objdiff | Compare compiled vs original | **objdiff-cli 3.8.2** in `.tools/objdiff/objdiff-cli.exe` (gitignored); project file `objdiff.json` — see `docs/progress.md` |
| WSL2 Ubuntu 26.04 | Linux build environment | Installed (`wsl -d Ubuntu -u root`); repo at `/mnt/c/...` |
| MIPS binutils | Assemble / link (R5900) | **`binutils-mips-linux-gnu` 2.45** in WSL: `mips-linux-gnu-as -EL -march=5900 -mabi=eabi`. Reassembly path — see `docs/toolchain.md` |
| EE cross C compiler | Matching C builds | **`ee-gcc2.96`** `2.96-ee-001003-1` in `tools/cc/ee-gcc2.96/` (gitignored, WSL) + wrapper `tools/cc/eegcc.sh` (needs `libc6:i386` and the `/usr/local/sce/ee/gcc` symlink) — see `docs/toolchain.md` §4.1. Pinned flags `-O2 -g2 -G8` in `config/compiler_flags.mk` |
| build script | Assemble/compile/link/hash | **`tools/build.py`** (WSL2) — mixed C+asm, gated on the flat-image SHA-1; `make check` |
| Phase-3 flag pinning | Pin compiler flags | **`tools/phase3_pin.py`** + `tools/matchcheck.py` — `docs/compiler.md` |
| Small-data audit | gp-relative vs absolute | **`tools/scan_sdata_access.py`** — `docs/compiler.md` §3 |
| Phase-6 loop | Per-function compile/diff | **`tools/eegcc.py`** (shared staging/flags, `cflags_for`: per-TU `-g` override), `tools/verify_c.py` (`--flags=` to try a per-TU level before listing), `tools/diff_func.py`, `tools/report.py`, `tools/gen_objdiff.py`, `tools/cc/show_compiled.sh` — `docs/progress.md` |
| Split-build internals | Constant multiply / padding | **`tools/cc/probe_mult.sh`** (R5900 `mult` vs shift/add, `docs/compiler.md` §4.2); `tools/build.py` pads a C object to its exact original span (`. = . + (span - size)`) — `docs/rebuild.md` |
| Phase-5 naming | Strings -> functions | **`tools/find_string_refs.py`** — `docs/naming-candidates.md` |
| IOP inventory | IRX modules (R3000) | **`tools/iop_inventory.py`** → `manifest/iop_modules.txt` |
| ELF container diff | our ELF vs original | **`tools/elf_container_diff.py`** — `docs/rebuild.md` §ELF container |
| 7z / isoinfo | ISO extraction | not installed; replaced by `tools/iso9660.py` (pure Python) |
| git | VCS | 2.55.0 (repo initialized) |
| python3 | Infra/tooling | 3.12.10 (Windows) / 3.14.4 (WSL) |
| node / npm | REA runtime | v24.21 / npm 11 |
| Java (JDK) | Ghidra runtime | 27 (accepted by Ghidra) |
| make / ninja | Build driver | **make 4.4.1 / ninja 1.13.2** (winget + WSL) |

**DISCOVERY (2026-10-13)**: REA CLI present and MCP-registered, but REA's
native analysis is **PE-only on Windows** and its cross-platform MIPS lane needs
standard MIPS32r2 + `SHT_MIPS_ABIFLAGS`, which the R5900/PS2 ELF lacks.

**SESSION 2 (2026-10-14):** REA deep lane re-verified unusable on Windows
(3-attempt workaround time-box documented in `docs/rea.md`); REA is used for
artifact inventory + evidence bundles. Primary disassembly = splat (per-function,
1037 files). Secondary view = Ghidra + Emotion Engine extension (100 % decode).
Reassembly toolchain = Debian `mips-linux-gnu` binutils in WSL2 (no Sony
`ee-as`/`ee-ld` needed). **Build environment = WSL2 (Ubuntu 26.04)**; Windows has
objdiff-cli 3.8.2, ninja 1.13.2, make 4.4.1. Matching C compiler
**`ee-gcc2.96` installed** under `tools/cc/ee-gcc2.96/` (gitignored, user-approved
download). **Phase 4 byte-exact rebuild PASSED**: flat load image 237,952 bytes,
SHA-1 `6f853f644a4279db18c15ceb8ee1d2a8b87a7b39`.

**SESSION 3 (2026-10-14):** Phase 3 **done** — flags pinned to **`-O2 -g2 -G8`**
by byte-level experiment (`tools/phase3_pin.py`, 11/11 cases), with a **per-TU
`-g0` override** (`tools/eegcc.py:cflags_for`) because the original mixes debug
levels and `-g` is *load-bearing* (`-g`/`-g2` suppress delay-slot filling).
Mixed C/asm build with the flat-image hash gate; **33 functions matched from C**
(504 / 203,692 `.text` bytes = 0.247 %); 13 NON_MATCHING attempts tracked in
`src/non_matching/` (hypothesis: a different EE-GCC *revision*). Naming started
(3 functions named from evidence). See `docs/archive-2026-10-14-session3.md`.

## 5. Phases

Work in order. Mark each phase when done and commit.

- [x] **Phase 1 — Extract.** ISO is at the **workspace root** (`Shadow of the Colossus (USA).iso`), not in `SHADOWDECOMP/`. Extracted 19 files with pure-Python ISO9660 (`tools/iso9660.py`, `tools/extract_iso.py`) → manifest in `manifest/files.txt`. Main ELF = **`SCUS_974.72`** (from `SYSTEM.CNF`, not `SCUS_973.24`).
- [x] **Phase 2 — Analyze.** `SCUS_974.72` parsed (sections/segments/entry); 319 strings. **Ghidra 12.1.4 + `ghidra-emotionengine-reloaded`** (`r5900:LE:32:default`) now decodes **100 %** of `.text` (50,923/50,923, 0 undefined; was 84 % with stock `MIPS:LE:32:default`). Function boundaries still "to be confirmed". See `docs/analysis.md`, `docs/rea.md`.
- [x] **Phase 3 — Compiler. DONE (2026-10-14, Session 3).** Flags pinned by byte-level experiment: **`-O2 -g2 -G8`**, with a **per-TU `-g` override** (`tools/eegcc.py:cflags_for`) because the original mixes debug levels (`func_00114C30` needs `-g0`; `-g`/`-g2` suppress delay-slot filling, so the level is load-bearing). 33 functions byte-exact out of the flag-pinning set + first batches; 13 functions recorded as NON_MATCHING with the hypothesis that the original is a different EE-GCC *revision*. Single source of truth: `config/compiler_flags.mk`. See `docs/compiler.md`.
- [x] **Phase 4 — Split & rebuild.** splat split is **per-function**: **1037 `.s`** under `asm/cod/` (one per function), `.text` 16-byte header as `textbin`; plus data segments, `build/SCUS_974.72.ld`, `include/macro.inc`. **Reassembly + link + hash check PASS**: `tools/build.py` (WSL2) → flat image byte-identical to the original, **237,952 bytes, SHA-1 `6f853f644a4279db18c15ceb8ee1d2a8b87a7b39`**. Still green with 33 functions replaced by C. See `docs/splat.md`, `docs/toolchain.md`, `docs/rebuild.md`.
- [~] **Phase 5 — Name.** In progress. `tools/find_string_refs.py` maps strings to the 66 functions that reference them; 2 functions named from direct evidence (`LoaderSysDumpIopModuleIdentifiers`, `OutputLinkerScriptFile`), the rest tabulated in `docs/naming-candidates.md`. Structs/data objects documented in `docs/structs.md`.
- [~] **Phase 6 — Decompile. STARTED.** 38 / 1037 functions matched from C (812 / 203,692 `.text` bytes = 0.399 %), all gated by the image hash. Loop + tooling in `docs/progress.md`; non-matching attempts in `src/non_matching/` (22 tracked).

## 6. Identifying the compiler

1. Pick 3–5 small, simple functions (leaf functions, getters, simple loops).
2. Write plausible C, compile with candidate flags (`-O2`, `-O1`, `-G0`/`-G8`, `-mgpopt`, `-fno-common`, etc.).
3. Compare with the original using objdiff.
4. Keep the flag set that matches the most functions. Record the winner and rejected candidates in `docs/compiler.md`.
5. Also check for GCC version hints in strings, and for libc/SDK code compiled with different flags than game code.

## 7. Decompiling a function (loop)

1. Read the target assembly (and its callers/callees if unclear).
2. Write C in `src/` with proper types (add structs to `include/` as they are confirmed).
3. Compile with the confirmed flags.
4. Diff against the original. Adjust (variable order, types, loop forms, temporaries) until it matches.
5. If stuck after reasonable attempts, keep a `#ifdef NON_MATCHING` version, leave the original asm included for the build, and write a short note on what differs.
6. Log the result in the Progress section.

Tips: use a function's constants, string references, and call patterns to infer types. Watch for delay slots, 64-bit register use, MMI/VU0 inline asm, DMA/GIF/VIF packet building, and scratchpad RAM access. For hand-written assembly or VU microcode that cannot be expressed in C, keep it as `.s` and note it.

## 8. Conventions

- **Naming:** functions `snake_case` by default; unknown ones keep auto names like `func_00123456` / `D_00123456` until evidence exists. Names come from evidence only.
- **Symbols:** keep `config/symbol_addrs.txt` as the single source of truth for names and addresses.
- **Structs:** document confirmed layouts in `docs/structs.md` with offsets and the evidence used.
- **Commits:** `phaseN: short description` or `decomp: function_name (matching)`.
- **Decisions:** any non-obvious choice goes in `docs/decisions.md` with date and reason.

## 9. Progress (update every session)

| Metric | Value |
|--------|-------|
| Current phase | Phases 1–4 done; **Phase 3 flags pinned**; Phase 5 in progress; **Phase 6 started: 38 functions matched** |
| ELF rebuild hash match | **YES — 237,952 bytes, SHA-1 `6f853f64…` (flat load image), still green with 38 functions from C** |
| Functions named | 3 (`entry`, `LoaderSysDumpIopModuleIdentifiers`, `OutputLinkerScriptFile`) + 66 string-reference candidates |
| Functions matched (C) | **38 / 1037** |
| Matched bytes | 812 / 203,692 `.text` bytes = **0.399 %** (verified) |
| Compiler flags | `-O2 -g2 -G8` (per-TU `-g0` override); `config/compiler_flags.mk` |
| `.text` disassembly (splat R5900) | accurate; **1037 per-function `.s`** |
| Ghidra EE-extension decode | **100 %** of `.text` (50,923/50,923) |
| splat split coverage | 203 KB / 85.6 % of ROM |
| Functions detected | 1037 (spimdisasm) |
| Non-matching attempts tracked | 22 (`src/non_matching/`) |
| IOP modules inventoried | 11 IRX (ELF32 MIPS-I, R3000A) |

### Session log

- **2026-10-14 (Session 4)** — sync + Phase 6 batch 3 (5 more functions) + compiler finding.
  - **Sync.** Rebuild re-verified before any change: `python3 tools/build.py` →
    `bin: 237952 bytes`, SHA-1 `6f853f64…`, **HASH MATCH** (33 from C, 1015 from
    asm). Session-3 results folded into sections 4/5/9; stale `560 B / 0.275 %`
    metric in `docs/decisions.md` corrected to the tool-reported `504 B /
    0.247 %` (`tools/report.py`); Session-3 tooling (small-data audit, Phase-6
    loop, ELF container diff) added to the tool table; `docs/structs.md`
    placeholder header removed. Commit `d3a877b`.
  - **Phase 6 batch 3 — 38 / 1037 functions now byte-exact** (812 / 203,692
    `.text` bytes = 0.399 %), image SHA-1 unchanged. New:
    `func_001028F0`/`func_00102930` (256-entry `.bss` table search, write `-1`),
    `func_00102A00`/`func_00102A40` (fill those tables with `-1`) and
    `func_0012E6D0` (guarded get-or-store with a local fallback). One trick worth
    keeping: the `-1` must be a *local initialised before the loop* so LICM
    materialises it before the loop bound (matching the original's instruction
    order).
  - **Compiler finding (docs/compiler.md §4.2).** The original uses the R5900
    3-operand `mult rd,rs,rt` for constant strides (`i*0x184`, `i*0x24`) but a
    shift/add sequence for `x*320`. `tools/cc/probe_mult.sh` shows `ee-gcc2.96`
    **never** emits `mult` for a *literal* constant under any ISA/CPU/`-O` flag
    (`-m3900` does, but changes `e_flags` to `mips1/3900`), while a *runtime*
    multiplier does — and the original's `addiu v1,$zero,0x184; mult a0,a0,v1`
    is exactly that shape. Reproducing it needs a local stride variable; four
    functions now match the multiply and differ only in register allocation, so
    they stay in `src/non_matching/`. This is concrete extra evidence for the
    different-revision hypothesis.
  - **Build fix (`tools/build.py`).** C objects were padded with `. = ALIGN(.,
    8)`, which over-pads the subsegments whose original span is only 4-byte
    aligned (`02E6D0`, span `0x34`, next `0x12E704`) and grew the image by 4
    bytes. Now a relative `. = . + (span - compiled_size)`. An absolute
    `. = <vaddr>` was tried and rejected (breaks `AT()` LMA → `ld` "small-data
    section too large").
  - **Tooling.** `tools/verify_c.py --flags=…` (try a per-TU `-g` before listing
    it), `tools/cc/show_compiled.sh` (disassemble what we compiled),
    `tools/matchcheck.py` now fails when the expected symbol is absent (a
    mis-named C function used to "match" and only fail at link time).
  - **Tracking.** 9 new NON_MATCHING attempts with `STATUS:` headers
    (`009B80`, `012380`, `0123C0`, `015008`, `020F18`, `021190`, `022018`,
    `0220F8`, `0262B8`) → 22 total. All are shape differences (allocation / block
    layout / loop rotation), none flag-fixable.

- **2026-10-14 (Session 4, start)** — sync. Rebuild re-verified before any change:
  `python3 tools/build.py` → `bin: 237952 bytes`, SHA-1 `6f853f64…`, **HASH MATCH**
  (1048 objects: 33 from C, 1015 from asm). Session-3 results folded into
  sections 4/5/9; stale `560 B / 0.275 %` metric in `docs/decisions.md` corrected
  to the tool-reported `504 B / 0.247 %` (`tools/report.py`); Session-3 tooling
  (small-data audit, Phase-6 loop, ELF container diff) added to the tool table;
  `docs/structs.md` placeholder header removed.

- **2026-10-14 (Session 3)** — Phase 3 flags pinned, mixed C/asm build, first 33 functions.
  - **Phase 3 (compiler flags) DONE.** `ee-gcc2.96` (`2.96-ee-001003-1`) runs in
    WSL after `libc6:i386` + a `/usr/local/sce/ee/gcc` symlink
    (`tools/cc/eegcc.sh`); its `cc1` cannot read sources on `/mnt/c` (drvfs), so
    sources are staged to ext4. Flags pinned by byte-level experiment:
    **`-O2 -g2 -G8`** — `tools/phase3_pin.py` compiles 11 cases and compares them
    against the original (`tools/matchcheck.py`). Key finding: **`-g`/`-g2` change
    codegen** (no delay-slot filling → `...; jr $ra; nop`), `-g0`/`-g3` do not
    match; the level is *sticky* in ee-gcc2.96. Small-data rule audited
    (`tools/scan_sdata_access.py`): 174/174 `%gp_rel` accesses resolve inside the
    gp window, 0 into it are absolute. Config: `config/compiler_flags.mk`,
    `docs/compiler.md`.
  - **Mixed C/asm build + objdiff.** `tools/build.py` now compiles functions
    listed in `config/c_sources.txt` from C and assembles the rest, with the
    flat-image SHA-1 as the gate (`make check`). A C object's `.text` is padded by
    the *linker* (align 8), never by `objcopy --update-section` (which drops
    relocations). `objdiff.json` + `tools/diff_func.py` + `tools/report.py` +
    `tools/verify_c.py` complete the loop.
  - **Phase 6 started: 33 functions byte-exact** (504 / 203,692 `.text` bytes =
    0.247 %), including `func_00114C30` which needed a per-TU **`-g0`**. 13
    attempts are tracked in `src/non_matching/` — none explained by any of 14
    extra `-f…`/`-m…` flags or by `-O1..-Os`; hypothesis: the original is a
    different **EE-GCC revision** (`docs/compiler.md` §4.1).
  - **Phase 5 started.** `tools/find_string_refs.py` links strings to the 66
    functions that reference them; 2 functions named from direct evidence, the
    rest tabulated in `docs/naming-candidates.md`; data objects/structs in
    `docs/structs.md`.
  - **REA re-tested from WSL2, still unusable** (2 attempts: no Linux node/java,
    Windows `node.exe` is still `platform=win32`; no bundled Linux Ghidra lane).
    New: `inspect_binary_layout` is x86-64-only. Session-3 metadata bundle:
    `docs/rea/evidence-bundle-session3.json` (2 records, 0 unknowns).
  - **Step 6 (optional).** ELF container diff documented
    (`tools/elf_container_diff.py`, `docs/rebuild.md`): ours is a single RWX
    `PT_LOAD` with `.cod`/`.cod_bss`, `e_entry` 0, `.symtab` retained, no
    `.mdebug.eabi64`; the original has 3 program headers and 15 sections.
    11 IOP modules inventoried (`manifest/iop_modules.txt`): ELF32 LE, EM_MIPS,
    MIPS-I (R3000A), flags `0x00000001`.

- **2026-10-14** — REA attach/use, EE Ghidra extension, per-function split, build env.
  - **REA**: MCP already attached (170 tools). Native lane re-verified unusable on
    Windows (PE-only gate); 3 workaround attempts time-boxed → (a) custom Ghidra
    language fails, (b) `ghidra-emotionengine-reloaded` v2.1.38 works for the
    **direct Ghidra** view, (c) derived ELF not pursued (host gate). REA used for
    artifact inventory (11 ELFs) + evidence bundle (`docs/rea/`). See `docs/rea.md`.
  - **Ghidra EE extension**: `r5900:LE:32:default` decodes **100 %** of `.text`
    (was 84 %).
  - **Per-function split**: `tools/gen_function_splits.py` → **1037 `.s`**; `.text`
    16-byte header marked data; coverage unchanged 85.60 %; instruction count
    exact (50,919 = 50,923 − 4). See `docs/splat.md`.
  - **Build env**: WSL2 Ubuntu 26.04; `binutils-mips-linux-gnu` 2.45
    (`mips-linux-gnu-as -EL -march=5900 -mabi=eabi`), gcc/cpp 15.2, ninja, make;
    Windows objdiff-cli 3.8.2, ninja, make. R5900 round-trip of `entry` verified.
    See `docs/toolchain.md`.
  - **Compiler**: corroborated `ee-gcc2.96` (`decompme/compilers`) via
    `Fantaskink/SOTC`; **user approved the download**; fetched to
    `tools/cc/ee-gcc2.96` (SHA-256 `0590d2ca…`).
  - **PHASE 4 BYTE-EXACT REBUILD PASSED.** `tools/build.py` (WSL2, Debian
    `mips-linux-gnu` binutils + `-mabi=eabi`) assembles the 1037 per-function
    `.s` + header + data and links them; the flat output is **byte-identical** to
    the original load image: 237,952 bytes, SHA-1 `6f853f64…`. Fixes along the
    way: n64 GPR names, `-mabi=eabi` for `ld %lo`, `objcopy` section alignment 4,
    strip splat's `ALIGN(.,16)`, route `.data_nop` into `.lit4`. See
    `docs/rebuild.md`.

- **2026-10-13** — DISCOVERY + Phase 1 + Phase 2 + Phase 4 split.
  - Found ISO at workspace root; main ELF is `SCUS_974.72` (per `SYSTEM.CNF`), not `SCUS_973.24`.
  - Installed Ghidra 12.1.4, set `GHIDRA_INSTALL_DIR`; registered REA MCP with OpenCode; installed REA skill.
  - **Blocker:** REA's native lane is PE-only on Windows; its MIPS lane needs MIPS32r2 + ABIFLAGS. R5900 not supported.
  - Extracted 19 ISO files with hashes (`manifest/files.txt`); `SCUS_974.72` SHA-1 `b715b349…`.
  - Parsed ELF (stripped, `e_flags 0x20924001` = ARCH_3/NOREORDER/MACH_5900, entry `0x00100010`).
  - Ghidra linear disasm: 84 % decoded (16 % R5900 gaps) — superseded below.
  - **Better engine found:** installed `splat64[mips]` (splat 0.50.1 + spimdisasm + rabbitizer) into `.venv`; Rabbitizer `R5900` category gives accurate decoding.
  - Built flat ROM (`tools/make_rom.py`) and config (`tools/splat_ps2_config.py`); `splat split` succeeded → accurate R5900 `asm/`, data segments, linker script, macros.
  - **Remaining blocker:** no EE toolchain (ee-as/ee-ld) → cannot reassemble/link/hash-check (Phase 3/4).

## 10. End-of-session checklist

Before ending, provide the user with:

1. Short summary of what was done and verified (hashes, match percentages).
2. Current project tree.
3. Prioritized TODO list for the next session.
4. Assumptions and uncertainties.

Then update sections 4 and 9 of this file and commit.
