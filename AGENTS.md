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
| REA (Reverse Engineering Anything) `rea-agents@6.4.0` | RE toolset + MCP server | Installed; **MCP registered with OpenCode**. Native lane unusable for PS2 on Windows (PE-only P0 profile) — see `docs/decisions.md` |
| Ghidra 12.1.4 | Native analysis (headless) | `C:\Users\Matheus\ghidra\ghidra_12.1.4_PUBLIC`; `GHIDRA_INSTALL_DIR` set. Language `MIPS:LE:32:default` (imperfect for R5900) |
| splat64 | Split ELF into asm/data | **0.50.1 installed** in `.venv` (+ spimdisasm 1.42.4, rabbitizer 1.16.2). `splat split config/SCUS_974.72.yaml` works — see `docs/splat.md` |
| objdiff / asm-differ | Compare compiled vs original | **MISSING** |
| EE cross toolchain (ee-gcc, ee-as, ee-ld, binutils-mips) | Build / reassemble | **MISSING** — blocks the byte-exact rebuild (Phase 4 hash check) |
| 7z / isoinfo | ISO extraction | MISSING — replaced by `tools/iso9660.py` (pure Python) |
| git | VCS | 2.55.0 (repo initialized) |
| python3 | Infra/tooling | 3.12.10 |
| node / npm | REA runtime | v24.21 / npm 11 |
| Java (JDK) | Ghidra runtime | 27 (accepted by Ghidra) |
| make / ninja | Build driver | **MISSING** |

**DISCOVERY (done 2026-10-13)**: REA CLI present and MCP-registered, but REA's
native analysis is **PE-only on Windows** and its cross-platform MIPS lane needs
standard MIPS32r2 + `SHT_MIPS_ABIFLAGS`, which the R5900/PS2 ELF lacks.
**Fallback in use: Ghidra headless driven directly** (`tools/ghidra_headless.bat`,
`tools/ghidra_scripts/*.java`). See `docs/decisions.md`.

## 5. Phases

Work in order. Mark each phase when done and commit.

- [x] **Phase 1 — Extract.** ISO is at the **workspace root** (`Shadow of the Colossus (USA).iso`), not in `SHADOWDECOMP/`. Extracted 19 files with pure-Python ISO9660 (`tools/iso9660.py`, `tools/extract_iso.py`) → manifest in `manifest/files.txt`. Main ELF = **`SCUS_974.72`** (from `SYSTEM.CNF`, not `SCUS_973.24`).
- [~] **Phase 2 — Analyze.** Loaded `SCUS_974.72` in Ghidra 12.1.4 (MIPS LE). Sections/segments/entry recorded; 319 strings; full linear disassembly (`build/SCUS_974.72.linear.txt`) is **84 % decoded** (16 % are undecodable R5900 MMI/COP2 words). Function boundaries are **unreliable** (Ghidra's recursive traversal breaks on R5900 gaps). See `docs/analysis.md`.
- [ ] **Phase 3 — Compiler.** Hypothesis (EE-GCC 2.9x / PS2 SDK 3.x) documented in `docs/compiler.md`; splat's `ps2elfinfo` also selects the `EEGCC` profile (independent corroboration). **Flag matching blocked on obtaining an EE cross-toolchain.**
- [~] **Phase 4 — Split & rebuild.** `splat` split succeeds → `asm/cod/000000.s` (accurate R5900), data segments, `build/SCUS_974.72.ld`, `include/macro.inc`. **Reassembly/link and hash check blocked on the EE toolchain.** See `docs/splat.md`.
- [ ] **Phase 5 — Name.** Evidence anchors collected (SDK banners, loader, kernel, GS, cdvd, mc2, net). See `config/symbol_addrs.txt`.
- [ ] **Phase 6 — Decompile.** Not started.

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
| Current phase | Phases 1–2 done; Phase 4 split done (rebuild blocked) |
| ELF rebuild hash match | no (no EE toolchain yet) |
| Functions named | 1 (`entry`); evidence anchors for SDK banners |
| Functions matched (C) | 0 / ~1500 (estimate) |
| Matched bytes | 0 % |
| `.text` spimdisasm/R5900 disassembly | accurate; `asm/cod/000000.s` |
| splat split coverage | 203 KB / 85.6 % of ROM |

### Session log

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
