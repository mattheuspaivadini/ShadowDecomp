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
config/              # splat YAML, symbol_addrs.txt, compiler flags, c_sources.txt,
                     # tu_flags.json, non_function_holes.txt, reloc_addrs.txt
asm/                 # split assembly per segment/function (asm/cod/*.s = 1042 + asm/data/)
src/                 # decompiled C: src/cod/ (matched) + src/non_matching/ (attempts)
include/             # headers, structs, SDK stubs (boot_globals.h, symbols.h, macro.inc)
tools/               # scripts, wrappers, diff helpers + tools/cc/ (EE-GCC revisions)
docs/                # decisions.md, compiler.md, structs.md, ledger.json, progress notes,
                     # *archive-*.md per session + docs/plan/ (master plan & worker tasks)
docs/plan/           # PLAN.md, tasks.tsv, TASK_STATE.tsv, WORKER_PROMPT.md, tooling.md,
                     # coverage.md, disc_inventory.tsv, ghidra/, scripts/
manifest/            # file list + SHA-1/MD5 hashes (commit this)
CONTEXT.md           # executive session summary (metrics + completed tasks)
AGENTS.md            # this file
```

`build/` (gitignored) also carries persistent scratch state: `build/plan/ctx/<stem>.md`
(pre-generated per-function context bundles), `build/plan/xff/` (overlay ELF splits),
`build/s8/drafts/`, `build/s10/verify_fast.py`, `build/s13/` (per-session scratch).

Create missing directories as needed. Keep this layout in sync with reality.

## 4. Tooling

Fill in the table during DISCOVERY and keep it current.

| Tool | Purpose | Status / path |
|------|---------|---------------|
| REA (Reverse Engineering Anything) `rea-agents@6.4.0` | RE toolset + MCP server | Installed; **MCP attached** (170 tools). Deep-analysis lane unusable for PS2 on Windows (PE-only gate) — use for artifact inventory + evidence bundles only. See `docs/rea.md` |
| Ghidra 12.1.4 + `ghidra-emotionengine-reloaded` v2.1.38 | Native analysis (headless) | `C:\Users\Matheus\ghidra\ghidra_12.1.4_PUBLIC`; EE extension language `r5900:LE:32:default` decodes **100 %** of `.text`. See `docs/rea.md` |
| splat64 | Split ELF into asm/data | **0.50.1 installed** in `.venv` (+ spimdisasm 1.42.4, rabbitizer 1.16.2). **Per-function split**: 1036 `.s` + 2 raw `textbin` under `asm/cod/` — see `docs/splat.md` |
| objdiff | Compare compiled vs original | **objdiff-cli 3.8.2** in `.tools/objdiff/objdiff-cli.exe` (gitignored); project file `objdiff.json` — see `docs/progress.md` |
| WSL2 Ubuntu 26.04 | Linux build environment | Installed (`wsl -d Ubuntu -u root`); repo at `/mnt/c/...` |
| MIPS binutils | Assemble / link (R5900) | **`binutils-mips-linux-gnu` 2.45** in WSL: `mips-linux-gnu-as -EL -march=5900 -mabi=eabi`. Reassembly path — see `docs/toolchain.md` |
| EE cross C compiler | Matching C builds | **`ee-gcc2.96`** `2.96-ee-001003-1` (default) + **`ee-gcc2.9-991111-01`** (`cc=29`) in `tools/cc/<asset>/` (gitignored, WSL); wrapper `tools/cc/eegcc.sh` selects one with `$EE_GCC_DIR` (needs `libc6:i386`; PE builds need `wine`). Get all revisions with `tools/cc/fetch_eegcc.sh`. Pinned flags `-O2 -g2 -G8` in `config/compiler_flags.mk` — see `docs/toolchain.md` §4, `docs/compiler.md` §4.3 |
| Compiler matrix | Revision question | **`tools/cc_matrix.py`** (compiler × function × flag-set match matrix; `--wine` for the PE builds) + `tools/cc_matrix_analyze.py`. Evidence: `docs/cc-matrix-session4.txt` |
| build script | Assemble/compile/link/hash | **`tools/build.py`** (WSL2) — mixed C+asm, gated on the flat-image SHA-1; `make check`. **This is the authoritative gate for a promotion**: it also fails on *undefined* symbols, which the relocation-masked `build/s10/verify_fast.py` cannot see (a draft calling `memcpy` passes `verify_fast` but not the link — this image's `memcpy` is `func_0012821C`, see the `0x0012821C` comment in `config/symbol_addrs.txt`) |
| Phase-3 flag pinning | Pin compiler flags | **`tools/phase3_pin.py`** + `tools/matchcheck.py` — `docs/compiler.md` |
| `-O` level discrimination | Pin the optimisation level | **`tools/opt_sweep.py`** (every manifest entry × `-O1/-O2/-O3/-Os`, per-TU flags/compiler kept) + `tools/cc/probe_olevels_diff.sh`, `tools/cc/probe_inline_dump.sh`; **`-O1` and `-Os` ruled out (39 / 14 counterexamples), `-O2` ≡ `-O3`** — `docs/compiler.md` §2.2, `docs/opt-sweep-session4.txt` |
| Small-data audit | gp-relative vs absolute | **`tools/scan_sdata_access.py`** — `docs/compiler.md` §3 |
| Phase-6 loop | Per-function compile/diff | **`tools/eegcc.py`** (shared staging/flags, `cflags_for`: per-TU `-g` override), `tools/verify_c.py` (`--flags=` to try a per-TU level before listing), `tools/diff_func.py`, `tools/report.py`, `tools/gen_objdiff.py`, `tools/cc/show_compiled.sh` — `docs/progress.md` |
| Candidate ranking | Pick the next tier | **`tools/find_candidates.py`**, `tools/dump_candidates.py`, `tools/list_unmatched.py` (leaf pool), `tools/list_callers.py` (1–2-call wrappers), `tools/archive_extra_c.py` (move a failed attempt to `src/non_matching/` with a `STATUS:` note) — `docs/progress.md` |
| Source permuter | Score source-shape variants | **`tools/permute.py`** (batch-compiles `build/permute/<stem>/*.c` with both compilers, scores each as an instruction edit distance with reloc bits masked; `--verbose` prints the aligned diff; logs to `docs/permute-log.md`). Resolved all 12 formerly-unexplained functions — `docs/non-matching-12.md` |
| Permuter batch + mutations | Re-attack the backlog at scale | **`tools/permute_batch.py`** (one staging + ROM load, many stems/variants; `--flag-sets ';-g0;-fno-optimize-sibling-calls'`; obj dirs tagged per flag set) + **`tools/permute_gen.py`** (13 mechanical text-mutation kinds: store order, arg order, unsigned, assoc, loop form, index-twice, casts, const-local, early return…). Session-6 backlog: `docs/non-matching-backlog.md` |
| Candidate survey | What is left to decompile | **`tools/fresh_candidates.py`** (unmatched, not in the backlog) + **`tools/classify_candidates.py`** (syscall / trampoline / real buckets) + **`tools/syscall_stubs.py`** (167 SDK `syscall` trampolines) + **`tools/dump_asm.py`** (compact per-stem asm dump) — Session 6 |
| Shape clustering | Find remaining families and clones | **`tools/shape_clusters.py`** (Session 7: normalizes every function to a shape token sequence — registers kept, immediates/branch targets abstracted — clusters the unmatched pool, finds exact/near clones of matched functions, classifies the hand-written/syscall pool; `--mnemonics` for shape-only clustering) — Session 7 |
| Constant-mismatch diff | Semantic bugs the edit distance hides | **`tools/const_diff.py`** (immediate-value multiset per function, reloc-masked; found the 019BE0 `0x200`/`0x2000` bug and 0121E8's 0x20-byte buffer) — Session 6 |
| Split-build internals | Constant multiply / padding | **`tools/cc/probe_mult.sh`** (R5900 `mult` vs shift/add, `docs/compiler.md` §4.2); `tools/build.py` pads a C object to its exact original span (`. = . + (span - size)`) — `docs/rebuild.md` |
| Phase-5 naming | Strings -> functions | **`tools/name_from_strings.py`** (authoritative: resolves `string -> function` from splat's `%hi/%lo` labels; `--json`) — `docs/naming-candidates.md`. Older heuristic `tools/find_string_refs.py` (window-6 `lui` pairing) is retained for the raw "which strings does a function touch" list but **under-reports** referents |
| Ledger (Session 8) | Single source of truth for every function | **`tools/gen_ledger.py`** → `docs/ledger.json` (**1044 records** = 1042 real functions + 2 `textbin`: `{addr,size,insns,kind,tu,cluster,compiler_cfg,status,attempts,notes}`; statuses `matched`/`near(N)`/`asm-permanent`/`untouched`/`textbin`). `--summary` prints the per-tier census |
| Wave loop (Session 8) | Drafting subagents + central scoring | **`tools/score_drafts.py`** (stages `build/s8/drafts/<stem>.c`, scores cc 29/296 × default/`-g0`/`-fno-optimize-sibling-calls`, then `--extra-cc` retries non-matching stems under the 2.95.x PE builds), **`tools/promote.py`**, **`tools/archive_draft.py`**, **`tools/fix_draft_header.py`** (repairs nested `/* */` in a header, which silently drops a draft from the score table), **`tools/wave_lists.py`** (tier lists + 12-stem chunks) — `docs/session8-plan.md` |
| Phase D (Session 8) | TU / call-graph / struct recovery | **`tools/infer_tu.py`** (specificity-weighted shared-symbol components + confirmed-config propagation → `config/tu_flags.json`), **`tools/callgraph.py`** (fraction of matched callees = bottom-up priority), **`tools/struct_infer.py`** (paste-ready struct skeletons from base+offset patterns) |
| Third generation (Session 8) | The image mixes **three** EE-GCC generations | `2.9-991111-*`, `2.96-ee-001003-1` and **`2.95.3-136` (PE, wine)**; `build/s8/sweep_allgen.sh` + `allgen-sweep.json`; `config/c_sources.txt` accepts `cc=wine:ee-gcc2.95.3-136` — `docs/compiler.md` §4.4 |
| Master plan & worker loop (Sessions 12–13) | Wave-based parallel decompilation | **`docs/plan/`**: `PLAN.md` (gap analysis + DAG + waves), `tasks.tsv` / `TASK_STATE.tsv` (54 dependency-ordered tasks), `WORKER_PROMPT.md` (per-task worker contract), `tooling.md`, `coverage.md`, `disc_inventory.tsv`. Scripts: `gen_tasks.py`, `update_state.py`, `check_plan.py`, `gen_context.py`, `xff_probe.py`, `xff_split.py`, `xff2elf.py`, `apply_shn_abs.py`, `irx_inspect.py`, `nico_dat_probe.py`. Gates: **`build/s10/verify_fast.py`** (~16 s, never `tools/verify_c.py`) + `tools/build.py` |
| Overlay (`.XFF`) split | KERNEL / MANAGER / GAMECORE | `build/plan/xff/{KERNEL,MANAGER,GAMECORE}.elf` + `*_syms.tsv` / `*_sections.tsv` + `{kernel,manager,gamecore}_asm/` (940 / 2277 / 2755 functions, byte-identical split); `build/plan/xff/boot_shn_abs.tsv` = the 840 official names + 65 globals — `docs/plan/PLAN.md` `WS-X` |
| Per-function context bundles | Worker input without broad scanning | **`build/plan/ctx/<stem>.md`** (**492** bundles) — address/size/status, inferred TU + compiler, callers/callees, referenced globals/strings, existing near-miss draft, full target asm, Ghidra pseudo-C hint. Regenerate: `python docs/plan/scripts/gen_context.py` |
| Boundary evidence | Is a `glabel` a real entry? | **`tools/ref_check.py`** (`jal`/`j` + `lui`-relative + literal-word reference counts for an address) — `docs/naming-candidates.md` §"Boundary re-check" |
| Non-function holes | Bad splat boundaries | **`config/non_function_holes.txt`** (addresses emitted as raw `textbin` by `tools/gen_function_splits.py` instead of `asm`) — `docs/naming-candidates.md` §"Boundary re-check" |
| IOP inventory | IRX modules (R3000) | **`tools/iop_inventory.py`** → `manifest/iop_modules.txt` |
| Hardware register map | Which EE registers does the image touch? | **`tools/scan_hw_regs.py`** (rebuilds every absolute `lui`+immediate address in `asm/cod/*.s`, keeps the `0x10000000`-`0x13FFFFFF` register range; `--func`/`--addr`/`--json`) — `docs/structs.md` §"Hardware registers" |
| ELF container diff | our ELF vs original | **`tools/elf_container_diff.py`** (`--ours` to compare any ELF) — `docs/rebuild.md` §ELF container |
| ELF container rebuild | Reproduce the original container | **`tools/containerize.py`** (run by `tools/build.py` after the link; `--check` requires byte-identity) — `docs/rebuild.md` §ELF container |
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

**SESSION 4 (2026-10-14): the revision question is RESOLVED — the image mixes two
EE-GCC generations.** Every EE-GCC build published in `decompme/compilers`
(8 Linux + 5 Windows/PE, the latter via wine 10.0) was compiled against all 59
functions we have C for (`tools/cc_matrix.py`; evidence
`docs/cc-matrix-session4.txt`). **No single revision matches everything**: the
`2.9-ee-991111(-01)` generation reproduces 9 functions `2.96-ee-001003-1`
cannot, and vice versa; the minimum cover is exactly
`{2.9-ee-991111-*, 2.96-ee-001003-1}` (47/59); 12 functions match neither.
`config/c_sources.txt` now carries a per-TU `cc=<token>` selector; the 9
"2.9-only" functions moved to `src/cod/`, so **47 functions are byte-exact**
(1148 / 203,692 `.text` bytes = 0.564 %) and the image SHA-1 is unchanged.
See `docs/compiler.md` §4.3, `docs/toolchain.md` §4.

**SESSION 5 (2026-10-14):** new permuter + all twelve "unexplained" functions
resolved; **148 functions matched**.
- **`tools/permute.py`** (new): batch-compiles source variants and scores each
  as an instruction edit distance (reloc bits masked), logging to
  `docs/permute-log.md`. It **resolved all 12 functions that no EE-GCC
  distribution reproduced** — every one a source-shape problem (expression
  parenthesisation, statement/store order, double indexing, early returns,
  `unsigned` fields, staged pointer adjustment). Per-function table:
  `docs/non-matching-12.md`.
- **Phase 6: 92 → 148 functions** (3308 → 6372 `.text` bytes, 1.624 % → 3.128 %)
  — the STEP-2 target (+40) was exceeded (+44) via the wrapper tier
  (`func_00107410` buffers, the 14-function `01B768`–`01BAA8` family), leaf
  helpers and permuter near-misses; 25 failures archived with `STATUS:` notes.
- **`-O2` vs `-O3` re-swept over all 148** (`docs/opt-sweep-session5.txt`):
  `-O1` 56/148, `-Os` 131/148 (ruled out), `-O2 ≡ -O3` 148/148 — **still not
  separable**; the image-side inlining evidence
  (`func_00102D70`'s inlined `_loadIopModuleFromEEBuffer`, no out-of-line copy)
  is consistent with `-O3` but also with `-O2` + `inline`. `-O2` stays pinned;
  the decisive experiment is writing that function with a plain `static` helper
  (Session 6 TODO). `docs/compiler.md` §2.3.
- **Phase 5: +3 names → 48 named `.text` symbols.** New evidence class: callee
  names from `func_00104668`'s failure diagnostics (`load_set_conf_only`,
  `get_interface_id`, `wait_get_addr_only`, all UNCONFIRMED); splat pipeline
  re-run end to end; hash green. The 18 pending candidates were not promoted
  (evidence rule held). `docs/naming-candidates.md`.
- Everything gated: `tools/verify_c.py` 148/148 byte-exact, `tools/build.py`
  HASH MATCH (237,952 B, `6f853f64…`) with the ELF container byte-identical at
  every commit. Archive: `docs/archive-2026-10-14-session5.md`.

## 5. Phases

Work in order. Mark each phase when done and commit.

- [x] **Phase 1 — Extract.** ISO is at the **workspace root** (`Shadow of the Colossus (USA).iso`), not in `SHADOWDECOMP/`. Extracted 19 files with pure-Python ISO9660 (`tools/iso9660.py`, `tools/extract_iso.py`) → manifest in `manifest/files.txt`. Main ELF = **`SCUS_974.72`** (from `SYSTEM.CNF`, not `SCUS_973.24`).
- [x] **Phase 2 — Analyze.** `SCUS_974.72` parsed (sections/segments/entry); 319 strings. **Ghidra 12.1.4 + `ghidra-emotionengine-reloaded`** (`r5900:LE:32:default`) now decodes **100 %** of `.text` (50,923/50,923, 0 undefined; was 84 % with stock `MIPS:LE:32:default`). Function boundaries still "to be confirmed". See `docs/analysis.md`, `docs/rea.md`.
- [x] **Phase 3 — Compiler. DONE (2026-10-14, Session 3; revision question resolved Session 4).** Flags pinned by byte-level experiment: **`-O2 -g2 -G8`**, with a **per-TU `-g` override** (`tools/eegcc.py:cflags_for`) because the original mixes debug levels (`func_00114C30` needs `-g0`; `-g`/`-g2` suppress delay-slot filling, so the level is load-bearing). The original is a **mix of two EE-GCC generations**: `2.9-ee-991111(-01)` and `2.96-ee-001003-1` (`tools/cc_matrix.py`, all 14 published revisions; no single one matches everything). 47 functions byte-exact; 12 recorded as NON_MATCHING and unexplained by any revision. **`-O2` discriminated from `-O1`/`-Os`** (Session 4 step 3: 92-function sweep, 39 / 14 counterexamples; `-O2` ≡ `-O3`). See `docs/compiler.md`, `docs/cc-matrix-session4.txt`, `docs/opt-sweep-session4.txt`.
- [x] **Phase 4 — Split & rebuild.** splat split is **per-function**: **1042 `.s`** under `asm/cod/` (one per function; 1036 after the Session-4 split + 6 merged boundaries separated by `T004` in Session 12) plus 2 raw `textbin` subsegments (the `.text` 16-byte header and the `0x00113074` non-function hole); plus data segments, `build/SCUS_974.72.ld`, `include/macro.inc`. **Reassembly + link + hash check PASS**: `tools/build.py` (WSL2) → flat image byte-identical to the original, **237,952 bytes, SHA-1 `6f853f644a4279db18c15ceb8ee1d2a8b87a7b39`**. Still green with 395 functions replaced by C. **Step 6 (ELF container) done (Session 4): `build/SCUS_974.72.elf` is byte-identical to the original `SCUS_974.72`** (242,940 bytes, SHA-1 `b715b349…`) — 3 program headers, real section names, `.mdebug.eabi64`, no symtab, `e_entry 0x00100010`; `tools/containerize.py` (run by `tools/build.py`). See `docs/splat.md`, `docs/toolchain.md`, `docs/rebuild.md`.
- [~] **Phase 5 — Name.** In progress. `tools/name_from_strings.py` (authoritative: resolves `string -> function` from splat's `%hi/%lo` relocation labels) finds **61 functions that reference a string carrying an identifier**; **50 are named, 11 are recorded candidates** (`docs/naming-candidates.md`). Names come from six evidence classes — *verbatim* self-naming log messages (17), *object* semaphore names with the routine inferred (22, UNCONFIRMED), three single inferences (`start`, `vfprintf`, `sceDbcGetDeviceStatus`, UNCONFIRMED), three *callee* names from `func_00104668`'s failure diagnostics (Session 5: `load_set_conf_only`, `get_interface_id`, `wait_get_addr_only`, UNCONFIRMED), 5 SDK object/operation names (Session 10a, UNCONFIRMED) and 2 more SDK names (Session 10a.2, UNCONFIRMED) — plus the two Session-3 names (`LoaderSysDumpIopModuleIdentifiers`, `OutputLinkerScriptFile`). Session 12 also imported **840 official `SHN_ABS` function names + 65 global object names from `KERNEL.XFF`** (`config/symbol_addrs.txt` is the single source of truth). **55 named `.text` symbols** (`entry` + 54 evidence-derived). `func_00113074` was re-checked and is a splat boundary false positive (unreferenced; see `config/non_function_holes.txt`). Structs/data objects documented in `docs/structs.md`.
- [~] **Phase 6 — Decompile. IN PROGRESS.** **395 / 1042 functions matched from C (31,652 / 203,692 `.text` bytes = 15.539 %)**, all gated by the image hash (`docs/ledger.json` holds 1044 records = 1042 real functions + 2 raw `textbin`). Session 7 ran a **shape-clustering + parallel-subagent drafting** loop (`tools/shape_clusters.py`, brief + central scorer in `build/s7/`); Session 12 executed the **master plan** (`docs/plan/PLAN.md`, waves `B001`–`B009`, `A001`–`A002`) via `tools/score_drafts.py` + `tools/promote.py`; Session 14 mined the authentic Newlib sources for `028xxx`–`031xxx` stems (7 matches, first-scoring in every case). Remaining real pool: **452** = 294 near-miss + 158 untouched. Non-matching attempts in `src/non_matching/` (294 tracked). See `docs/non-matching-backlog.md`, `docs/archive-2026-10-14-session7.md`, `docs/plan/`.

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
| Current phase | Phases 1–4 done (**incl. step 6, ELF container**); **Phase 3 revision question resolved** (Session 8 added a **third** generation, `2.95.3-136`); **Phase 5 in progress (55 named symbols)**; Phase 6: **395 functions matched** |
| ELF rebuild hash match | **YES — 237,952 bytes, SHA-1 `6f853f64…` (flat load image), still green with 395 functions from C** |
| ELF container (whole file) | **YES — `build/SCUS_974.72.elf` byte-identical to the original: 242,940 bytes, SHA-1 `b715b349…`; 3 program headers, 16 sections, `e_entry 0x00100010`, `.mdebug.eabi64`, no `.symtab`** (`tools/containerize.py`) |
| Functions named | **55 `.text` symbols** = `entry` + **54 evidence-derived names**: 17 verbatim self-naming log messages, 22 inferred from `SceStdio<Op>Sema` object names (UNCONFIRMED), 3 single inferences (UNCONFIRMED), 3 callee names from `func_00104668` failure diagnostics (Session 5, UNCONFIRMED), 2 Session-3 names, 5 SDK object/operation names (Session 10a, UNCONFIRMED), 2 more SDK names (Session 10a.2, UNCONFIRMED) |
| String-evidenced name candidates | **61 functions** reference an identifier-bearing string; **50 named, 11 pending** (Session 10a applied 5 with no C body/caller; Session 10a.2 applied the 2 that Session 10a had reverted after they broke the link, via a pure symbol rename of the 21 matched C call sites) |
| Functions matched (C) | **395 / 1042** (2.9-991111, 2.96 and 2.95.3-136 per TU; the wrapper tier uses a per-TU `-fno-optimize-sibling-calls` on cc=296 TUs only — the 2.9 `cc1` rejects the flag) |
| Matched bytes | 31652 / 203,692 `.text` bytes = **15.539 %** (verified) |
| Compiler flags | `-O2 -g2 -G8` (per-TU `-g0` and `-fno-optimize-sibling-calls` overrides, the latter cc=296-only); `-O1`/`-Os` ruled out on 148 functions; `-O2 ≡ -O3` (not separable; Session 6 ran the decisive experiment — §2.4 of `docs/compiler.md`: plain static + `-O3` ≡ `inline` + `{-O2,-O3}`, so the `-O2` pin stays) |
| Compilers | `ee-gcc2.96` (default) + `ee-gcc2.9-991111-01` (`cc=29`) + **`wine:ee-gcc2.95.3-136`** and `ee-gcc2.9-991111-xz`; matrix in `docs/compiler.md` §4.3, third-generation verdict in §4.4 |
| `.text` disassembly (splat R5900) | accurate; **1042 per-function `.s` + 2 raw `textbin`** (`.text` header, `0x00113074` non-function hole) |
| Ghidra EE-extension decode | **100 %** of `.text` (50,923/50,923) |
| splat split coverage | 203 KB / 85.6 % of ROM |
| Functions detected | **1042** real functions (`docs/ledger.json`: 1044 records = 1042 + 2 `textbin`); 1037 spimdisasm boundaries − 1 false positive (`0x00113074`) = 1036, then `T004` split 6 merged boundaries (+6) in Session 12 |
| Non-matching attempts tracked | **294** (`src/non_matching/`; ledger: 294 near / 158 untouched / 195 asm-permanent → 452 real pool remaining) |
| IOP modules inventoried | 11 IRX (ELF32 MIPS-I, R3000A) |
| EE hardware registers referenced | **38 addresses** (`tools/scan_hw_regs.py`); the 2 that were unidentified are now **confirmed**: `0x10001010` = `T2_MODE` (Timer 2 mode/status), `0x1000E060` = `D_STADR` (DMAC stall address) — `docs/structs.md` §"Hardware registers" |

### Session log

- **2026-10-16 (Session 14) — authentic-Newlib-source mining, +7 matched functions (388 → 395, 14.404 % → 15.539 %, 29,340 → 31,652 B) + stale-doc reconciliation.**
  - **Method that worked.** The untouched pool has a large Newlib block (`028xxx`–`031xxx`). Drafting those from the
    *authentic upstream source* (raw mirror `https://raw.githubusercontent.com/eblot/newlib/master/newlib/libc/<dir>/<file>`,
    kept in `build/s13/newlib/`) instead of from ASM prose matched **every** one of them on the **first scoring run**; the ASM is
    then only needed to confirm the platform adaptation (non-reentrant `_r` variants, `Pack_32`, IEEE_8087, `Sudden_Underflow`
    off, `_DOUBLE_IS_32BITS` off).
  - **Matches (all cc=296, default flags, score 0 on the first draft):**
    - `030D78` (`__submore`) — `BUFSIZ` = 1024 explains the `0x400` malloc and `p += 0x3FD`; the reent comes from `fp->_data`
      (0x54) and `_r`/`_p` sit at 0x04/0x00.
    - `02E9C8` (`_s2b`) — older signature `(void *p, const char *s, int nd0, int nd, unsigned int y9)` (`y9` in `$a4`, EABI).
    - `02DA90` (`fread`) — non-reentrant variant calling `__srefill`; no flockfile/ORIENT code is emitted in this build.
    - `02EF80` (`_lshift`, Pack_32) — `k >> 5` (`sra`), the `k1++` in the `maxwds` doubling delay slot and the countdown
      zero-fill loop all fall out of the authentic source.
    - `02E578` (`__smakebuf`) — `st_mode` at stat+0x04 (confirmed by the matched `fstat` stub `src/cod/012088.c`), `__SNPT`/`__SOPT`
      as 0x800/0x400, `fp->_blksize = 1024` at 0x4C, `ptr->__cleanup` at reent+0x3C; the frame (0x90, saved registers at 0x70) pins
      `sizeof(struct stat)` into (0x68,0x70], so the size is padded explicitly (the only field read is `st_mode`); this build has
      **no `__SSTR` guard** in the `_malloc_r` failure arm and no asprintf path.
    - `02F3A0` (`_b2d`) and `02F538` (`_d2b`) — the `union double_union` + `word0(x) = x.i[1]` / `word1(x) = x.i[0]` (IEEE_8087)
      macros reproduce the `and` + `dsll32/or` word writes exactly; `_d2b` needs the `!Sudden_Underflow` shape
      (`if (de) { *e = de - Bias - (P-1) + k; *bits = P - k; } else { *bits = 32 * i - hi0bits(x[i-1]); }`, Bias + P - 1 = 1075).
  - **Near-misses archived.** `013780` (`sceGsPutDrawEnv`, cc=29, 4 iterations, best 12, 58/58 insns) and `029930` (official
    `vfprintf`, cc=296, 29/29 insns, frame 0x20). `029930`'s residual is allocation-only: the original does **not** keep the reent
    live across `__sinit` (the tail call re-reads `fp->_data`), and ee-gcc then swaps `$s1`/`$s2` (`fmt`/`ap`) and picks the
    branch-likely form of the `__sdidinit` test.
  - **Reclassifications (asm-permanent).** `028BB0` (`strcat`) and `028CDC` (`strchr`) are hand-vectorised MMI
    (`lq`/`psubb`/`pnor`/`pcpyld`/`pcpyud`, `pxor`) — not expressible in pure C, so they stay `.s`. `tools/gen_ledger.py`'s
    `ASM_PERMANENT_EXTRA` is now a `{stem: reason}` map and writes the reason into `docs/ledger.json`.
  - **Documentation reconciliation.** `AGENTS.md`, `CONTEXT.md` and `docs/plan/PLAN.md` carried stale numbers (pre-`T004` /
    pre-Session-12); every metric was re-derived from `tools/gen_ledger.py --summary` plus `config/c_sources.txt` and
    `asm/cod/`. `A003`/`A005` are now `WIP` in `docs/plan/TASK_STATE.tsv` with per-stem results.
  - **Gates.** `build/s10/verify_fast.py` → **395/395 byte-exact**; `tools/build.py` → flat image **HASH MATCH** (237,952 B,
    `6f853f64…`) with the ELF container byte-identical; `docs/ledger.json` regenerated (**395 matched / 31,652 B / 294 near /
    195 asm-permanent / 158 untouched / 452 real pool**).

- **2026-10-16 (Session 13) — Reference-architecture review.** Compared the
  local NTSC-U `SCUS_974.72` project against `Fantaskink/SOTC` and prepared a
  DeepSeek translation prompt. The upstream targets the Preview `SCPS_150.97`,
  so it is useful as corroborating interface evidence only, never as an ABI
  authority for the NTSC-U binaries. The local boot image is byte-exact with
  388 C-matched functions; KERNEL/MANAGER/GAMECORE XFF parsing and splitting are
  established, while game-domain collision, IK, map streaming, and typed
  gameplay interfaces remain unimplemented overlay work.

- **2026-10-16 (Session 12) — Master Plan execution (Waves B001–B009, A001–A002), +32 matched functions (356 → 388, 12.892 % → 14.404 %, 26,260 → 29,340 B).**
  - **Promotions (B007–B009):**
    - `00F4C0` (`SetTLBEntry`, wine:2.95.3-136) — argument forwarding into `$a0` preserved branch delay `$ra` save.
    - `013368` (`sceVif1PkAddGsData`, cc=296) — post-increment pointer store sequence.
    - `014C48` (`sceDmaSend`, cc=29) — `sceDmaChan` volatile `tadr`, `0xFFFFFFFFU` unsigned comparison.
    - `014CB0` (`sceDmaSendN`, cc=29) — volatile `madr`, `| 0x101`.
    - `014D28` (`sceDmaSendI`, cc=29) — volatile `madr`, `| 0x109`.
    - `014DA0` (`sceDmaRecv`, cc=29) — channel control bitmask manipulation.
    - `01D988` (`func_0011D988`, cc=29) — conditional expression error code mapping.
    - `028630` (`_sbrk_r`, cc=296) — authentic Newlib reentrant `sbrk` wrapper.
    - `031100` (`_close_r`, cc=296) — authentic Newlib reentrant `close` wrapper.
    - `013B00` (`sceGsSwapDBuff`, cc=29) — per-branch `__asm__ volatile("");` preventing sibling call.
    - `01A5C8` (`sceMc2ChangeThreadPriority`, wine:2.95.3-136) — array declaration preventing `$gp` small-data access.
    - `01A600` (`sceMc2iChangeThreadPriority`, wine:2.95.3-136) — identical twin calling `iChangeThreadPriority`.
    - `028970` (`_kill_r`, cc=296) — authentic Newlib reentrant `kill` wrapper.
    - `031158` (`_fstat_r`, cc=296) — authentic Newlib reentrant `fstat` wrapper.
    - `004DF8` (`padsysInit`, cc=296) — `int buf[8]` stack frame allocating `0x20` local bytes.
    - `01D8E0` (`func_0011D8E0`, cc=29) — array of `0x898`-byte structs indexing with `mult 0x898`.
  - **Promotions (B001–B006 + A001–A002):**
    - `00AB58` (`sceFsReset`, cc=29) — fixed GP-relative `.data` section attribute on `D_00132314`.
    - `012B98` (`sceSifExitCmd`, cc=29) — array declaration on `D_0014B354` to avoid `-G8` small data.
    - `02EC38` (`_i2b`, cc=296) — exact Newlib `mprec.c` `_Bigint` return and field store order.
    - `002BD8` (`LoaderSysDeleteAllExternalThreadExceptMe`, cc=296) — promoted.
    - `02EAF8` (`_hi0bits`, cc=296) — promoted.
    - `02E3F8` (`_fwalk`, cc=296) — exact Newlib `fwalk.c` `--i >= 0` loop form.
    - `02EB78` (`_lo0bits`, cc=296) — exact Newlib `mprec.c` trailing zero count logic.
    - `00A7C8` (cc=296), `027448` (cc=296) — split boundary and leaf helpers.
    - `00FC90` (`GetSystemCallEntry`, cc=29) — fixed scalar global `D_00132988` small data GP addressing.
    - `00E3C8` (`sceSifLoadFileReset`, cc=29) — array declaration on `D_00132330` preventing GP addressing.
    - `007768` (`InitThread`, cc=29, 236 B) — official syscall symbols + inline assignment in `CreateSema`.
    - `010120` (`ExecPS2`, cc=29, 112 B) — return type `int` preventing premature tail call.
    - `0311B8` (`_lseek_r`, cc=296, 96 B) — authentic Newlib `lseek_r` shape.
  - **Waves completed & tracked:** `B001`–`B009`, `A001`, `A002` marked `DONE` in `docs/plan/TASK_STATE.tsv`.
  - **Gates:** `verify_fast.py` (388/388 byte-exact in 16–44 s), `tools/build.py` (237,952 B flat image HASH MATCH + byte-identical 242,940 B ELF container).


- **2026-10-15 (Session 11a) — near-miss campaign, +3 functions (346 → 349, 12.21 % → 12.397 %, 24,876 → 25,252 B).**
  - **New pattern — empty-asm register pin** `asm volatile ("" : "+r" (x));` (emits no code, forces the value
    through a register): `010FA0` (materialises the `D_00133918` `lui/addiu` base) and `030AF0` (keeps the
    return value out of the tail call's delay). The `"memory"`-clobber form fences dbr: `010E00` (plain
    `beqz`+`nop` instead of `beqzl`+duplicated store). All three at cc=29, promoted via `promote.py`.
  - `028850` (best 1 @ cc=296, 3 rounds / 8 variants) and `022210` (best 2 @ cc=29, 3 rounds / 8 variants)
    stay archived with residuals: dbr plain-vs-annul bit and error-path arg-copy order.
  - Gate: HASH MATCH (237,952 B, `6f853f64…`) + container byte-identical + 349/349 byte-exact
    (`build/s10/verify_fast.py`, 21 s vs ~1.5 h serial; handoff: `build/s10/handoff_11a.md`).
- **2026-10-15 (Session 10b) — diff-driven hard cases (+1 function, 343 → 344, 11.977% → 12.083%, 24,612 B).**
  - **Method:** classify the residual diff first (`build/s10/pdiff.py`: permute.py on `build/s10/perm/<stem>/` + side-by-side disassembly), then one targeted C lever per class. Notes: `build/s10/notes_10b.md`; handoff `build/s10/handoff_10b.md`.
  - **`028778` 1 → 0 (MATCH, cc=296, 1 iteration).** Residual = operand order of one commutative `addu` (`$v0,$v1` vs `$v1,$v0`); fixed by `index * 4 + ctx[0x75]`. Promoted via `promote.py`; gate HASH MATCH + container byte-identical + `verify_c.py` 344/344; commit `821adf9`.
  - **`022550` 3 → 3 (3 iterations, 17 variants).** Residual = register allocation only: the `%hi(D_00135958)` pseudo and the loaded value swap `$v0/$v1` (same schedule). Store order, temps, volatile, struct, local extern, const-local base/n: no change. Archived (`archive_draft.py`). **Command family stopped by rule**: `0229B0 022A38 022CE0` not touched.
  - **New pattern (commutative operand order):** a 1-insn diff where `addu rd,rs,rt` has rs/rt swapped is fixed by swapping the C operands (`i*4 + base` vs `base + i*4`); permuter body/decl-order mutations do not cover it.
  - Ledger: **344 matched / 328 near / 191 asm-permanent / 173 untouched / 501 real pool**.
- **2026-10-15 (Session 10c) — triage + volume, 0 matches (344 unchanged, 12.083%).**
  - **Step 0 (triage):** 11 near(<=2) stems listed; all skipped — `build/s10/perm/` holds only Session 10b perm data (022550, 028778), so `pdiff.py` cannot classify any diff. 0 matches. Stop (>5 consecutive skipped).
  - **Step 1 (45-80 tier):** blocker — lot-1 stems require callee signatures + global/struct types not available; speculative drafts cannot match. EE-GCC toolchain confirmed functional (002FE0 smoke test byte-exact). Lot 1 = 0/0 → STOP per 0/10 rule. Remaining 37 stems saved to `build/s10/w45s_remaining.txt`.
  - Ledger unchanged: **344 matched / 328 near / 191 asm-permanent / 173 untouched / 501 real pool**.
- **2026-10-15 (Session 10c.3) — triage + one lot, +2 functions (344 → 346, 12.083% → 12.21%, 24,612 → 24,876 B).**
  - **PART 1 triage:** all 11 stems scored via pdiff.py; 2 matched via a single store-order/removed-store lever — `0155D8` MATCH cc=29 (dropped redundant pre-loop `p->f00 = 0`), `02E490` MATCH cc=296 (swapped `a0[0x30]=a1;` before `a0[0x34]=a2;`). Both promoted via promote.py; gate HASH MATCH + container byte-identical. Remaining 9 stems archived (best score 1-2; classes: register allocation / branch layout / scheduling).
  - **PART 2 lot 1 (45-80 tier):** all 10 stems (018380 029878 031048 011B98 020370 018970 020F30 02F6C0 0214D0 016FB0) drafted + scored once; 0 matches (scores 34-52; 3 compile errors on complex call-chain stems). Hit rate 0%. Lot 1: drafted 10 / matched 0 / hit rate 0%.
  - Ledger: **346 matched / 326 near / 191 asm-permanent / 173 untouched / 499 real pool**; matched bytes 24,876.

- **2026-10-15 (Session 10a.2) — mechanical symbol rename: the two SDK names Session 10a reverted are applied (+0 functions, 343 unchanged, 11.977%).**
  - **Task.** Apply `SceSifrpcCall` 0x00109980 and `SceMrpcBind` 0x00119C08 (the two names Session 10a renamed, then reverted because the rename broke the link) as a **pure symbol rename** — no C body, no flag, no other symbol.
  - **References found (Grep over `src/`, `asm/`, `config/`, `include/`).** `func_00109980`: 20 compiled `src/cod/` callers + 28 archived `src/non_matching/` attempts + the `asm/`-generated call sites; `func_00119C08`: `src/cod/019BE0.c` + 2 `src/non_matching/` attempts. No `include/` references; `config/` had only comments (no `symbol_addrs.txt` entry existed). Historical logs under `docs/` were left untouched.
  - **Applied.** Two new `config/symbol_addrs.txt` entries (`SceSifrpcCall = 0x00109980`, `SceMrpcBind = 0x00119C08`); the identifiers renamed at every call site in `src/` (50 C files, 127 occurrences) and in the `config/c_sources.txt` comments; the splat pipeline re-run end to end, which regenerated `asm/` (2 `glabel` files + 48 `jal` targets) and `config/SCUS_974.72.yaml`. 103 files changed; every `asm/` diff is exactly the old→new substitution.
  - **Gate.** `tools/build.py` → **HASH MATCH** (237,952 B, `6f853f64…`), `containerize.py` → **byte-identical to the original**; `tools/verify_c.py` → **343/343 byte-exact** (4-TU spot check first, incl. the wine `2.95.3-136` `019BE0`).
  - **Naming.** Named `.text` symbols 53 → **55**; string-evidenced candidates now **50 named / 11 pending** (`docs/naming-candidates.md` updated; decision recorded in `docs/decisions.md`).

- **2026-10-15 (Session 10a) — permuter pass (no gain) + SDK naming promotion (+0 functions, 343 unchanged, 11.977%).**
  - **Task 1 (near-miss permuter, 5 targets): no target improved.** `028778` 1→1, `022550` 3→3, `0229B0` 3→3, `022A38` 3→3, `022CE0` 3→3; ~400 `permute_gen.py` body/decl-order mutants per stem scored with `score_drafts.py` (cc 29/296 × default/`-g0`/`-fno-optimize-sibling-calls` + 3rd-gen PE retry). Log: `build/s10/permuter_pass.log`. No promotions; best mutant = the already-archived attempt, so no re-archive.
  - **Task 2 (SDK naming): 5 string-evidenced, UNCONFIRMED names applied** to no-C-body/no-C-caller functions — `SceSifrpcBind` 0x001097A0, `sceDbcInit` 0x00115A88, `sceCdInit` 0x00116FB0, `SceMrpcUnbind` 0x00119DD8, `sceMc2Init` 0x0011A188 (naming-only). **2 more were reverted after a gate failure**: `SceSifrpcCall` 0x00109980 (20 matched C TUs call it) and `SceMrpcBind` 0x00119C08 (`src/cod/019BE0.c`) — the rename left their `func_*` references undefined, and fixing it needs a C-source edit out of scope. Matched candidates and thread/infrastructure object names stay withheld (`docs/naming-candidates.md`, `docs/decisions.md`).
  - **Gate:** splat pipeline re-run end to end (1036 asm + 2 textbin); the first pass (7 names) broke the link, the 2 names referenced from matched C were reverted, and the second pass changed only 19 `asm/` files, all of them rename substitutions; `tools/build.py` → **HASH MATCH**, container byte-identical; `tools/verify_c.py` byte-exact.
  - **Ledger regenerated:** the committed `docs/ledger.json` was stale (43 Session-9 archives not folded in) — now **343 matched / 329 near / 191 asm-permanent / 173 untouched / 502 real pool**.

- **2026-10-15 (Session 9) — wave loop (parallel drafting + central scoring),
  +13 functions (330 → 343, 11.007% → 11.977%).** Archive: `docs/archive-2026-10-15-session9.md`.
  - **Floor target +40 NOT met; stretch +60 NOT met.** Primary blocker: subagent
    budget exhausted — R2 wave B (w45s_3–6, 37 stems) received zero drafts.
  - **Step 0 (baseline).** Gate re-verified: HASH MATCH, 330/330, 22,420 bytes
    (11.007%), ledger 330 matched / 233 near / 191 asm-permanent / 282 untouched.
  - **Step 1 (score-≤3 residue, 15 stems).** 2 matches: `00A070`, `018870` (both
    cc=29); 10 near ≤3.
  - **R1 wave (w25b 36 + wcg 48 = 68 stems).** 10 matches (8 cc=29, 2 cc=296),
    6 near ≤3. Combined hit rate 14.7%.
  - **R1 gate:** promoted 12 → HASH MATCH, 342 from C (11.828%).
  - **Step 3 (clone-of on 12 new matches).** Only actionable: `022AD8`/`022B58`
    ≈ `0229B0`/`022CE0` (dist 4, command family).
  - **Step 4 (naming).** 61 string-evidenced candidates; 46 in untouched 45+
    tiers. SDK identities confirmed (`sceGsPutDrawEnv`, `sceGsSyncPath`,
    `sceGsDefDispEnv`, `SceMrpcBind0/1`, `SceCd*Sema`, `SceStdio*`, `start`).
    No new promotions.
  - **R2 wave A (pilot 8 + w45s_0/1/2 36 = 44 stems).** 1 match: `01C578`
    (cc=29, 304 B); 1 near score 1: `028778` (cc=296). Hit rate 2.3% (expected
    ~10%). Pilot 81-150: 0/8.
  - **R2A gate:** promoted `01C578` → HASH MATCH, 343 from C (11.977%).
  - **43 failures archived** to `src/non_matching/`.
  - **Tooling updates:** `score_drafts.py --only-draft`,
    `shape_clusters.py --clone-of*`, `archive_draft.py --drafts-dir/--session`,
    `build/s9/score_multi.py`, `build/s9/gate.sh`.

- **2026-10-14 (Session 7) — shape clustering + parallel drafting waves, +72
  functions (212 → 284).** Archive: `docs/archive-2026-10-14-session7.md`; live
  plan/scoreboard: `docs/session7-plan.md`.
  - **Step 0 (baseline).** Gate re-verified before any change (HASH MATCH +
  container byte-identical + 212/212). True baseline computed: 1036 functions,
  **824 remaining, 219 non-C** (167 syscall stubs + 52 other hand-written
  bodies) → **realistic C pool 605**; the target was restated against it
  (20 % = +121, 50 % = +302).
  - **Step 1 (shape clustering).** New `tools/shape_clusters.py` (shape tokens,
  clone detection, `--mnemonics` mode) + `build/s7/wrap_scan.py`. Finding: the
  cheap families are exhausted (only four full-shape clusters of size ≥ 3), so
  the session is per-function work.
  - **Step 2 (waves).** 12 drafting subagents in waves of ~12 functions
  (`build/s7/BRIEF.md` + central `build/s7/score.py`, cc 29/296 × default/`-g0`/
  `-fno-optimize-sibling-calls`): waves **0** (3), **1a** (4), **1b** (7),
  **1c** (7), **1d** (3), **2a+2b** (11), **2c** (1), **3a** (5), **3b** (8),
  **3c** (2), **4a** (6), **4b** (4) + the targeted fixes below.
  - **Step 3 (targeted).** Solved the Session-6 backlog pair `027500` / `00A798`
  and eight more stems with the permuter (`0101D8 0230B0 022BD8 022C30 022C88
  006310 00A0B0 026140`).
  **New winning patterns (all byte-exact):** a callee declared returning
  **64-bit** makes an `int` wrapper emit `dsll32/dsra32`; a **`void`** callee
  frees `$v0` for the next statement's base; an **asm memory barrier** preserves
  store order (`013228`); **`void` prototypes on wrapper+tail-callee** make cc=29
  emit the 2.9-frame tail `j`; the **const-local pattern** fixes the `$s0/$s1`
  role allocation of the `func_00123260` command family.
  - **Step 4 (naming).** No new evidence; 48 named symbols unchanged; no splat
    re-run.
  - Closing: `tools/build.py` → **HASH MATCH** + container byte-identical;
  `tools/report.py` → **284/1036, 15,820/203,692 B = 7.767 %**; 124 near-misses
  archived; history commits `29f50bd 64f9372 f42589d 30cf06b 8064757 822ddd5
  9caabd3 96a0213`.

- **2026-10-14 (Session 6) — permuter re-attack, -O2/-O3 verdict, +64 functions
  (148 → 212).** Archive: `docs/archive-2026-10-14-session6.md`. STEP 0 (sync +
  count reconciliation) was done by a *different model session* (`ad45ea2`,
  +3 functions `010910 011F90 0120D0`); steps 1–4 ran here, with a parallel
  model session intermittently active in the same worktree (its batch drafts
  were adopted and re-verified — waves 1–4 below).
  - **Step 1 — backlog re-attack.** `docs/non-matching-backlog.md` (every
    remaining stem, best edit distance over all rounds, family notes, the new
    winning patterns). Promoted `011C50 020D10 00F0F0 0121E8 01B718 01B740`.
    Key findings: the literal must be a named local *after* the call
    (`00F0F0`); **cc=29 does not sibling-call-optimise and its cc1 rejects
    `-fno-optimize-sibling-calls`** (the flag is cc=296-only); `-g0` fills the
    `jr` delay but did not close the six score-2 stems.
  - **Step 2 — `-O2` vs `-O3` decided (mechanism).** `func_00102D70` with plain
    static helpers: `-O2` keeps the helpers out of line (648 B, 76-insn
    caller), `-O3` integrates them (604 B, 151 insns) and is byte-identical to
    the `inline` control at both levels; neither is byte-exact yet, so the
    `-O2` pin stays — `docs/compiler.md` §2.4.
  - **Step 3 — +64 in four waves.** Wave 1 (`0000C0 010118 0188E0 018928
    018CE0 019020 019138 019180 0191C8 019450 022D68 022DE0 021E88`): the
    018xxx block-store family + tail-call wrappers are cc=29-only. Wave 2
    (`0288E8 028908 028930 028950 029800 02C208 02C220 02D9E0 02E530 02E558
    02FB90 030AC8 030D48` at the default compiler + `010400 010410 010420
    031940 031A80` at cc=29). Wave 3 (13): the nine **sceStdio\* tail-call
    trampolines** (`003008 003020 003038 003050 003068 003080 0030C8 0030E0
    0030F8`, frame + `j` = cc=296) and four **variadic register-save stubs**
    (`003FF8 004040 005948 005990`, reproduced byte-for-byte by a plain
    `void f(int a0, ...) {}`). Wave 4 (11): `022DA0` (cc=29), the
    `func_00107010` + `sync`/`ei` family (`007C48 021058 023180`), and the
    `func_0010FB20`-gated wrapper family (`010EA0 011050 011168 0112D0 011390
    010DB8 00F118`, cc=29 — the single trailing `return b;` is load-bearing:
    with an early return the `beqz` targets the epilogue instead of the shared
    `v0 = b` copy). `020708`/`020748` + six drafts archived.
    New tools: `tools/permute_batch.py` (multi-stem/flag-set scoring),
    `tools/permute_gen.py` (mechanical mutations), `tools/const_diff.py`
    (immediate-multiset diff — found the 019BE0 constant bug and 0121E8's
    0x20-byte buffer), `tools/fresh_candidates.py`,
    `tools/classify_candidates.py`, `tools/syscall_stubs.py`.
    Finding: the image contains **167 hand-written syscall trampolines**
    (`addiu $v1,$zero,N; syscall 0; jr $ra; nop`, 125 in the 0x106BC0-0x107120
    syscall table) — SDK assembly, kept as `.s`, not C candidates.
  - **Step 4 — naming.** No new evidence; 48 named symbols unchanged; the
    18 pending candidates keep their documented reasons.
  - Closing: `tools/verify_c.py` → **212/212 byte-exact**; `tools/build.py` →
    **HASH MATCH** + container byte-identical.

- **2026-10-14 (Session 4, closing) — session archive written and the gate
  re-verified.** `docs/archive-2026-10-14-session4.md` records the whole session
  (scope, per-step evidence, reproduction commands, metrics, assumptions, Session-5
  TODO); it supersedes the mid-session draft that stopped at "Phase-6 batch 3".
  Closing verification: `tools/build.py` → **HASH MATCH** (237,952 B,
  `6f853f64…`) with the whole ELF container byte-identical, and
  `tools/verify_c.py` → **92/92 byte-exact**. Metrics table (section 9) reconciled
  to the tool-reported 1036 real functions (1037 splat boundaries − 1 false
  positive).

- **2026-10-14 (Session 4, step 6) — the ELF container is reproduced and the
  whole file is byte-exact.**
  - **New tool `tools/containerize.py`** (run by `tools/build.py` after the
    link): reshapes the raw `ld` output (`build/SCUS_974.72.ld.elf`, one RWX
    `PT_LOAD`, one `.cod` section, symtab retained) into the original container
    at `build/SCUS_974.72.elf`. Content (every loadable byte) is taken from our
    own `.cod`; the layout (section table, program headers, entry) is recovered
    from the original. Result: **byte-identical to `extracted/SCUS_974.72`**
    (242,940 bytes, SHA-1 `b715b3496aad6f7601a0ab8495acd1d151a1ff7b`), with
    3 program headers (`PT_MIPS_REGINFO` + RO `.text` + RW data), 16 sections
    (`.text .text_nop .reginfo .data .ctors .dtors .eh_frame .rodata .lit4
    .data_nop .sdata .sbss .bss .mdebug.eabi64 .shstrtab`), and no
    `.symtab`/`.strtab`. **`tools/elf_container_diff.py` reports zero
    differences** (it gained `--ours` to compare any ELF).
  - **Entry point.** `ld -e entry` sets `e_entry = 0x00100010` (the `entry`
    symbol). Measured on the raw `ld` output: the `e_entry` row disappears from
    the container diff; the remaining gaps (1 phdr, 6 sections) are then closed
    by the container pass. Progression table in `docs/rebuild.md`.
  - **`.reginfo` / hash subtlety.** The pinned flat image excludes
    `SHT_MIPS_REGINFO` (`tools/make_rom.py`), so its 24 `.reginfo` bytes are
    zero; the original ELF's own `objcopy -O binary` includes them (`$gp =
    0x00141D70`) and hashes to `325b0c60…` (same 237,952 bytes; only 3 bytes
    differ). `tools/build.py` gates the hash on the raw `ld` output and
    `containerize.py` fills the real `$gp` from our linker's own `_gp` symbol,
    so the flat-image gate (`6f853f64…`) and the whole-file hash both hold.
  - **Why not a linker script.** splat's PS2 config has no segment type for
    `.text_nop`/`.reginfo`/`.ctors`/`.dtors`/`.eh_frame`/`.data_nop` (all fall
    back to `data`) and one 0x54-byte `.data` subsegment
    (`asm/data/cod/031BAC.data.s`) holds `.text_nop` + `.reginfo` + padding,
    which a linker cannot split; a native reproduction would need those
    generated `.s` files regenerated with distinct sections. Recorded in
    `docs/rebuild.md` §"Why not a linker script" and `docs/decisions.md`.
  - **Verification.** `tools/build.py` → **HASH MATCH** (237,952 B,
    `6f853f64…`) and container byte-identical; `tools/elf_container_diff.py` →
    no differences; `tools/verify_c.py` → 92/92 byte-exact.

- **2026-10-14 (Session 4, step 5) — the two unidentified hardware registers are
  identified (`T2_MODE`, `D_STADR`), both CONFIRMED against public references.**
  - **New tool `tools/scan_hw_regs.py`**: reconstructs every absolute address
    built by a `lui`+immediate pair in `asm/cod/*.s` (the same text that is
    assembled for the byte-exact rebuild) and keeps the addresses inside the EE
    register range `0x10000000`-`0x13FFFFFF`: **38 addresses**, none of them
    resolving back into the image. Two reconstruction bugs were found and fixed
    while writing it: `(0x… >> 16)` must be masked **after** the shift, and
    load/store displacements are **signed** (`lui $at,0x10010000` with
    `sw -0x1000($at)` is `0x1000F000`, not `0x1001F000`). The tool also reports
    read/write counts and read-modify-write sequences per address.
  - **`0x10001010` = EE Timer 2 MODE (`T2_MODE`) — confirmed.** Sources: ps2sdk
    `ee/kernel/include/timer.h`, ps2sdk `common/include/ee_regs.h`
    (`A_EE_T2_MODE`, "Timer 2 mode/status"), PCSX2 `pcsx2/Hw.h`
    (`RCNT2_MODE = 0x10001010`) and PS2Tek "EE Timers" (`10000010h + N*800h`,
    bit layout). Usage (10 reads, 1 RMW, 3 write helpers): `func_00110640`
    returns `MODE & 3` = **clock source**; `func_00110430` programs
    `(old & ~3) | arg | 0x300`, plus `0xC80` when idle (`0x300` =
    CMPE|OVFE, `0xC80` = timer enable + clear the two flags) — i.e. *start
    Timer 2 with a clock source* — and registers `func_001109D0` as the INTC
    handler for **cause 11 = Timer 2** (`syscall 0x10` = `AddIntcHandler`);
    `func_00110C78`/`_001109D0`/`_00110780` test bit 10 (compare flag) / bit 11
    (overflow flag) and maintain the 64-bit software time base `D_00133918`;
    `func_00110410` is a MODE write helper that uses the **KSEG1 alias
    `0xB0001010`**. Sibling `T3_MODE` (`0x10001810`) is read by `func_001102B8`.
  - **`0x1000E060` = EE DMAC Stall Address (`D_STADR`) — confirmed.** Sources:
    ps2sdk `ee/dma/include/dma_registers.h` (`DMA_REG_STADR 0x1000E060`,
    "Stall Address Register"), ps2sdk `common/include/ee_regs.h`
    (`A_EE_D_STADR`) and PCSX2 `pcsx2/Hw.h` (`DMAC_STADR`). `func_00114C30` is a
    32-bit read-old/write-new pair on it (and is *unreferenced* in the image —
    dead libdma code, so its SDK name stays UNCONFIRMED); the whole block
    `0x1000E000`-`0x1000E060` plus `D_ENABLER`/`D_ENABLEW` (0x1000F520/0x1000F590)
    is used by `func_00114940` (reset of the 10 channels + `D_STAT`),
    `func_00114A20` (env put: `D_CTRL` via the documented `DMA_SET_CTRL` field
    positions, then `D_PCR`/`D_SQWC`/`D_RBSR`/`D_RBOR`) and `func_00114F58`
    (DMA hold: `D_ENABLER`/`D_ENABLEW` bit 16).
  - **Bonus (HYPOTHESIS, routine names only):** the cluster
    `0x001102B8`-`0x00110D40` is very likely ps2sdk's `ee/kernel/timer.c` — T2
    as the 64-bit system-time base, a sorted alarm list
    (`func_00110910`/`_00110998`), and an `mfc0 $12`/`di`/`sync.p`/`mtc0
    $ra,$30`/`eret` wrapper (`func_00110390`/`_00110410`) for the register write.
    Per-routine candidate table in `docs/structs.md`; every name stays
    **UNCONFIRMED** (the *register* identification does not depend on it).
  - **Applied**: named macros in `include/symbols.h` (`EE_T2_MODE`,
    `EE_D_STADR`, the DMAC global block, `EE_D_ENABLER`/`_ENABLEW`,
    `EE_T2_COUNT`, `EE_T3_MODE`); `src/cod/010640.c` and `src/cod/014C30.c`
    now use them. `tools/verify_c.py 014C30 010640` → **2/2 byte-exact**,
    `tools/build.py` → **HASH MATCH** (237,952 B, `6f853f64…`).
  - **Fixed**: the EE memory-map table in `docs/structs.md` listed the timers at
    `0x1000F000`-`0x1000F300` and the GS at `0x1000E000` — both wrong. It is
    replaced by the documented map (timers at `0x10000000`+N*0x800, DMAC globals
    at `0x1000E000`, INTC at `0x1000F000`, SIO at `0x1000F100`, SBUS/PGIF at
    `0x1000F200`/`0x1000F300`, GS privileged at `0x12000000`, `GS_CSR` at
    `0x12001000`) with per-claim references; a table also identifies the other
    36 register addresses the image touches.

- **2026-10-14 (Session 4, step 4) — Phase 5 naming pass; the `func_00113074`
  boundary is a false positive.** Naming goes from 3 to **45 named `.text`
  symbols** (`entry` + 44 evidence-derived), and the split is re-run and
  hash-verified.
  - **New tool `tools/name_from_strings.py`** (authoritative): resolves
    `string -> function` from **splat's own `%hi/%lo` relocation labels** in
    `asm/cod/*.s`, and classifies each string as *verbatim* (the routine's own
    diagnostic names it — `"sceDbcSendData2: rpc error"`), *object* (a semaphore
    the routine creates for itself — `"SceStdioReadSema"`), *bare*, or *assert*.
    It found **61 functions** with an identifier-bearing string (Session 3's
    `tools/find_string_refs.py` window-6 heuristic reported 66 and missed 11 real
    referents; it now carries a warning).
  - **Applied 43 names**: 17 *verbatim* (`LoaderSysLoadIopModuleFromEEBuffer`,
    `setNewIopIdentifier`, `sceGsPutDrawEnv`/`sceGsSyncPath`/`sceGsDefDispEnv`,
    ten `sceDbc*`, `sceCdChgSys`, `sceSifMCallRpc` — all UNCONFIRMED-free because
    the function's own message states the name), 22 *object*-rule `sceStdio*`
    (each verified to lazily create its own per-operation sema at the operation
    site), plus `start`, `vfprintf` and `sceDbcGetDeviceStatus` marked
    UNCONFIRMED. `LoaderSysLoadIopModuleFromEEBuffer` is the one function whose
    body inlines two static helpers, which is why it references three names.
  - **18 candidates left pending with reasons** (thread names, `bare` object
    names, multi-object inits, pure sema-creation helpers) — table in
    `docs/naming-candidates.md`.
  - **`func_00113074`: the proposed size-8/size-12 split is contradicted by the
    call graph.** 0x00113074 has no reference of any kind (no `jal`/`j`, no
    `lui`+immediate, no literal word), its only instruction is a `jr $ra` whose
    delay slot is the *first* instruction of 0x00113078, and 0x00113078 has 8
    `jal` callers — so splitting there would delete the entry those callers need.
    New mechanism `config/non_function_holes.txt` +
    `tools/gen_function_splits.py` emits it as a 4-byte `textbin` (raw bytes)
    instead of `asm`: no function is invented and the image is byte-identical.
    The **six other non-8-byte-aligned starts** (0x0012821C, 0x001282CC,
    0x00128CDC, 0x00128E6C, 0x001290C4, 0x0012E704) all have **2–55 callers** and
    stay real: 8-byte alignment is not a validity criterion here.
  - **Symbol-rename plumbing.** splat parses everything after `;` on a
    `symbol_addrs.txt` line as `attr:value` pairs, so comments moved to their own
    lines; five matching C sources (`00C058/00C230/00C600/00CFB8/00D408`) had
    their `func_0010BEA8` callee renamed to `sceStdioCCode` or the link failed.
  - **Verification.** Pipeline re-run end to end (`splat_ps2_config.py` → base
    split → `gen_function_splits.py` → `rm -rf asm` → clean split): 1036 `asm` +
    2 `textbin`, coverage 85.60 %. `tools/build.py` → **HASH MATCH** (237,952 B,
    `6f853f64…`); `tools/verify_c.py` → **92/92 byte-exact**.

- **2026-10-14 (Session 4, step 3) — the optimisation level is discriminated.**
  New tool **`tools/opt_sweep.py`**: compiles every entry of
  `config/c_sources.txt` at `-O1/-O2/-O3/-Os` (keeping the per-TU `-g` /
  `-fno-optimize-sibling-calls` and the `cc=29` revision; an explicit `-O…`
  replaces the pinned `-O2`, `tools/eegcc.py:cflags_for`). Result over the 92
  matched functions: **`-O1` 53/92** (39 counterexamples), **`-O2` 92/92**,
  **`-O3` 92/92**, **`-Os` 78/92** (14 counterexamples). **`-O1` and `-Os` are
  ruled out; `-O2` is confirmed over them.** `-O2` and `-O3` are *not*
  separated — they emit identical code for all 92 (and for all 36
  `src/non_matching/` attempts too). This is structural: in GCC 2.9x/2.96 the
  only `-O3` delta is `-finline-functions`, and no TU here has an inlinable
  helper (`tools/cc/probe_olevels_diff.sh`, `tools/cc/probe_inline_dump.sh`).
  The level cannot be narrowed past `{-O2,-O3}` without a function whose body
  contains an inlined static helper; either reproduces the image, so `-O2` is
  kept. Evidence: `docs/compiler.md` §2.2, `docs/opt-sweep-session4.txt`.
  - Two ≥30-instruction candidates written for this step —
    `func_00110910` (33 insns, sorted-list insert) and `func_0012EAF8`
    (32 insns, binary-search clz) — are archived in `src/non_matching/`: both
    reproduce the control flow but are non-matching (register allocation; EE-GCC
    if-conversion into `movn`). No matched function reaches 30 insns (largest:
    23). `tools/find_candidates.py` gained `--min-insns`. Image hash unchanged.

- **2026-10-14 (Session 4, step 2)** — Phase 6 batch: 47 → **92 functions**
  (1148 → 3308 bytes, 0.564 % → 1.624 %), image SHA-1 unchanged.
  - **New tooling.** `tools/list_unmatched.py` (un-matched leaf pool),
    `tools/list_callers.py` (small functions with 1–2 calls — the wrapper tier),
    `tools/archive_extra_c.py` (moves a failed `src/cod` attempt into
    `src/non_matching/` with a `STATUS:` header), `tools/gen_progress_table.py`.
  - **Leaf tier (19).** Word-copy family (`_0010F370`, `_0010FC08`,
    `_0010FE50`, `_00110270`, all `cc=29`); list/table code (`_00110998`
    unlink, `_001028A0` pair search, `_00109640` nested list search,
    `_00106B58` 60-column record store); strings (`_0011BF68`, `_00129578`);
    byte/LEB128 (`_001148E0`, `_00125998`, `_001259E0`); struct stores
    (`_00119AA0`, `_001220B0`, `_00121EC0`, `_00120438`, `_0012D7F0`,
    `_00114020` with an inline `sync`).
  - **Call wrappers (26).** `tools/list_callers.py` found ~100 small callers.
    26 of them matched once the per-TU `-fno-optimize-sibling-calls` flag was
    added: ee-gcc folds `call; return` into a `j` tail call, but the original
    emits `jal` + epilogue. The image itself contains 107 `j func_*` tail calls,
    so sibling-call optimisation is a per-TU flag (like the per-TU `-g`).
  - **Archived attempts (22).** `src/non_matching/` grew to 34. The dominant
    new family is the **pipelined 256-entry table scan**
    (`_00102790`/`_001027E0`/`_00102830`/`_00102970`): ee-gcc loads the value
    one iteration ahead and saves the index before the increment; no plain
    `for`/`while`/`do-while` reproduces it under either revision. Other
    families: loop peel + branch-likely (`_0010FC40`), delay-slot placement
    (`_00107C70`, `_00111F90`, `_001120D0`), block layout (`_00110EF0`),
    register allocation (`_0011288`, `_0013368`, `_0012C78`, `_0011BAE8`,
    `_0011BBB8`, `_0011C50`, `_0013098`, `_0011C138`, `_0011C198`,
    `_0027048`, `_0020D10`), if-chain lowering (`_00117A00`).
  - **Evidence.** `tools/verify_c.py` is 92/92 byte-exact; `tools/build.py` →
    HASH MATCH (237,952 B, `6f853f64…`).

- **2026-10-14 (Session 4, revision resolution)** — the compiler-revision
  question, end to end.
  - **Candidate inventory.** Every EE-GCC asset in `decompme/compilers` fetched
    and unpacked (`tools/cc/fetch_eegcc.sh`); 13 EE-GCC archives = 8 Linux (ELF
    i386) + 5 Windows (PE) builds, plus the two extra PE patch levels in
    `ps2_compilers.tar.xz`. Versions and hosts tabulated in
    `docs/toolchain.md` §4.1. The wrapper/install scripts were generalised so
    many distributions coexist (`$EE_GCC_DIR`, auto-detected `cc1`/assembler
    dirs); PE builds run through wine 10.0 via a `wine:<name>` selector in
    `tools/eegcc.py`.
  - **Matrix.** `tools/cc_matrix.py` compiles all 59 functions we have C for (47
    matching + 12 non-matching) with every candidate under `-O2 -g2 -G8` and
    `-g0` and compares each with the original (`tools/matchcheck.py`). Full
    output in `docs/cc-matrix-session4.txt`; summary table in `docs/compiler.md`
    §4.3.
  - **Verdict: no single revision.** Totals: 2.9-990721 37, 2.9-991111(-01/a)
    38, 2.9-991111-01-dtls13010 39, 2.95.2-273a 34, 2.95.3-* 33, 2.96 38,
    3.2-* 19, 3.2-030210-beta2 (Cygwin) will not run under wine. **Union 47/59;
    the minimum cover is exactly `{2.9-ee-991111-*, 2.96-ee-001003-1}`; 12
    functions match neither.**
  - **e_flags / mdebug.** The original's `.mdebug.eabi64` is stripped to size 0
    and there is no `.comment`, so the revision could not be read from the ELF.
    `e_flags` *does* discriminate: the 2.9/2.95 family emits `0x20924001` (the
    original's flags), `2.96` emits `0x20924000` (NOREORDER bit clear), 3.2
    `0x20920001`.
  - **Applied fix.** `config/c_sources.txt` gained a per-TU `cc=<token>` selector
    (`cc=29` -> `EE_C_COMPILER_29`); the 9 "2.9-only" functions moved from
    `src/non_matching/` to `src/cod/`. `tools/verify_c.py` is 47/47 byte-exact;
    `tools/build.py` → HASH MATCH (237,952 B, `6f853f64…`). §4.2 corrected: the
    `mult` constant-stride shape is a *2.9-vs-2.96* difference, and the literal
    form now matches (`int size = 0x184;` workaround removed).
  - **New tooling tracked:** `tools/cc_matrix.py`,
    `tools/cc_matrix_analyze.py`, `tools/cc/fetch_eegcc.sh`,
    `tools/cc/eegcc_versions.sh`, `tools/cc/eegcc_inventory.sh`,
    `tools/cc/find_compiler_strings.py`; `tools/eegcc.py` and `tools/build.py`
    resolve the per-TU compiler; `tools/cc/eegcc.sh` + `install_prefix.sh` are
    generic.

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

## 11. Plan workflow (`docs/plan/`)

All worker tasks, disc/coverage measurements, `.XFF` overlay specs, and pre-generated per-function context bundles live under `docs/plan/` and `build/plan/`:

1. **Master plan & gap analysis:** [`docs/plan/PLAN.md`](file:///C:/Users/Matheus/Documents/ShadowDecomp/docs/plan/PLAN.md)
2. **Task table & live state:** [`docs/plan/tasks.tsv`](file:///C:/Users/Matheus/Documents/ShadowDecomp/docs/plan/tasks.tsv) (54 dependency-ordered tasks across `WS-T`, `WS-D`, `WS-B`, `WS-A`, `WS-X`, `WS-C`, `WS-E`) and [`docs/plan/TASK_STATE.tsv`](file:///C:/Users/Matheus/Documents/ShadowDecomp/docs/plan/TASK_STATE.tsv)
3. **Worker prompt:** [`docs/plan/WORKER_PROMPT.md`](file:///C:/Users/Matheus/Documents/ShadowDecomp/docs/plan/WORKER_PROMPT.md)
4. **Tooling, REA & Ghidra headless scripts:** [`docs/plan/tooling.md`](file:///C:/Users/Matheus/Documents/ShadowDecomp/docs/plan/tooling.md) and `docs/plan/ghidra/`
5. **Disc inventory & measured coverage:** [`docs/plan/disc_inventory.tsv`](file:///C:/Users/Matheus/Documents/ShadowDecomp/docs/plan/disc_inventory.tsv) and [`docs/plan/coverage.md`](file:///C:/Users/Matheus/Documents/ShadowDecomp/docs/plan/coverage.md)
6. **Pre-generated worker context bundles (`489` functions) & `.XFF` symbol tables (`840` official `SCUS_974.72` function names + `5,972` overlay functions):** `build/plan/ctx/<stem>.md` and `build/plan/xff/` (regenerate anytime with `python docs/plan/scripts/xff_probe.py && python docs/plan/scripts/gen_context.py`).
7. **Direction of truth for symbols:** `config/symbol_addrs.txt` is canonical; import into Ghidra via `docs/plan/ghidra/ImportRepoSymbols.java`. Never run slow `tools/verify_c.py` (~1.5 h); always gate tasks with `python build/s10/verify_fast.py` (~11 s) and `python docs/plan/scripts/check_plan.py`.
