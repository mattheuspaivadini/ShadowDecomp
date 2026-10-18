# AGENTS.md — Shadow of the Colossus (USA, PS2) Decompilation

> Read this file at the start of every session. Historical logs, the full tooling table, per-session notes and metrics live in [`CONTEXT.md`](CONTEXT.md); update that file (not this one) with progress.

## 1. Project summary

Matching decompilation of the main executable **`SCUS_974.72`** of *Shadow of the Colossus* (NTSC-U, PS2), built from the owner's legally owned copy.

- **Target:** MIPS R5900 (Emotion Engine), little-endian, with MMI and VU0 macro-mode.
- **Success:** rebuild the ELF from our asm + C and obtain a byte-exact hash match (flat image SHA-1 `6f853f644a4279db18c15ceb8ee1d2a8b87a7b39`, 237,952 B; ELF container 242,940 B, SHA-1 `b715b349…`).
- **Compilers:** the image mixes three EE-GCC generations, selected per translation unit in `config/c_sources.txt` via `cc=` (`ee-gcc2.96` default, `cc=29` = `2.9-991111-01`, `wine:ee-gcc2.95.3-136`). Base flags `-O2 -g2 -G8`, with per-TU overrides (`-g0`, `-G0`, `-fno-optimize-sibling-calls` on cc=296 only, `-fno-schedule-insns`, `-fno-strict-aliasing`).
- **Layout:** `asm/` split assembly (one `.s` per function), `src/cod/` matched C, `src/non_matching/` near-miss attempts (with `STATUS:` headers), `include/` headers/SDK stubs, `config/` splat YAML + symbols + `c_sources.txt`, `tools/` scripts, `docs/` notes (`docs/plan/` master plan), `manifest/` hashes. `extracted/` and `build/` are gitignored.
- **Status:** see `docs/ledger.json` (`python tools/gen_ledger.py --summary`) and `CONTEXT.md`. Phases 1–4 are done (byte-exact rebuild); Phase 5 (naming) and Phase 6 (decompilation) are in progress.
- **Source of truth:** `config/symbol_addrs.txt` (names/addresses), `config/c_sources.txt` (functions built from C), `docs/ledger.json` (per-function status).

## 2. Build and verification commands

Build environment is WSL2 (Ubuntu); the `Makefile` wraps WSL for you. Run from the repo root.

| Command | Purpose |
|---|---|
| `make check` (= `make build`) | Full build via `tools/build.py`; **fails unless the flat-image SHA-1 matches** and the ELF container is byte-identical. Authoritative gate. |
| `python build/s10/verify_fast.py [<stem>...]` | Fast per-function byte-exact check (~16–40 s for all; pass a stem for one function). Relocation-masked, so it cannot see undefined symbols — always follow with `make check`. |
| `python docs/plan/scripts/check_plan.py` | Validates the plan/task state. |
| `make diff F=<func>` | Build and diff one function. |
| `make report` / `python tools/gen_ledger.py --summary` | Progress and ledger census. |
| `make container` / `make elf-diff` | Check/inspect the ELF container. |
| `make verify` | Slow (~1.5 h) full `verify_c.py`; **do not use** for routine gating. |

Long builds or sweeps: run in the background and poll. Heavy parallel compiler sweeps can crash WSL2 — run one sweep at a time at `--jobs 4`.

Useful decompilation helpers: `tools/permute*.py` (source-shape/type/statement mutations), `tools/score_drafts.py`, `tools/promote.py`, `tools/archive_draft.py`, `tools/diff_func.py`, `tools/name_from_strings.py`. Full table in `CONTEXT.md`.

## 3. Code and workflow conventions

- **Language:** respond to the user in Portuguese; write code, comments, commits and docs in English.
- **Evidence over guesses.** Never invent function names, struct layouts or behavior. Mark guesses with `// UNCONFIRMED: <reason>`. Unknown symbols keep `func_XXXXXXXX` / `D_XXXXXXXX`.
- **Naming:** functions `snake_case` by default unless an SDK/Newlib name is evidenced; names are recorded only in `config/symbol_addrs.txt`. After a rename, re-run only `splat split config/SCUS_974.72.yaml`. **Do not re-run `tools/gen_function_splits.py`** (it drops the hand-made T004 splits).
- **Structs:** document confirmed layouts in `docs/structs.md` with offsets and evidence; use typed structs (field types affect GCC scheduling/TBAA).
- **C style:** match the surrounding code (comment density, naming, idiom); prefer natural SDK-style C over transliterated `*(int *)(p + off)`; reference string literals and file-statics by their image labels (a C object may not add `.rodata`/`.sdata`).
- **Decompilation loop:** read the target asm (and callers/callees) → write C in `src/cod/<stem>.c` → add a line to `config/c_sources.txt` with the right `cc=`/flags → score with `verify_fast.py <stem>` → adjust (variable order, types, loop forms, temporaries, callee return types/arity) until byte-exact. If stuck, archive in `src/non_matching/` with a `STATUS:` note; hand-written/MMI/VU asm stays `.s`.
- **Commits:** one function (one draft) per commit, containing only that promoted or re-archived draft and its `config/c_sources.txt` line.
  - `decomp: <function_name> (<stem>) matching`
  - `non-matching: <function_name> (<stem>) <old score> -> <new score>`
  - `phaseN: short description` for phases; `docs:` for log/metrics updates (own commit).
  - Commit only after `verify_fast.py <stem>` and a full `make check` hash match.
- **Decisions:** non-obvious choices go in `docs/decisions.md` with date and reason. Don't ask for confirmation between phases unless a decision is irreversible.
- **Failures:** diagnose, try at least two alternative approaches, then report the blocker with the exact error output.

## 4. Test instructions

There is no unit-test suite; correctness *is* byte-exactness. For every change:

1. **Single function:** `python build/s10/verify_fast.py <stem>` must report 1/1 byte-exact.
2. **Full image:** `make check` must print `HASH MATCH` (237,952 B, SHA-1 `6f853f64…`) and the container must be byte-identical (`containerize.py --check` runs inside the build).
3. **Whole set:** `python build/s10/verify_fast.py` must report N/N byte-exact, where N equals the number of entries in `config/c_sources.txt`.
4. **Ledger/plan:** after promotions run `python tools/gen_ledger.py` and `python docs/plan/scripts/check_plan.py`.
5. A promotion that fails the link (undefined symbol, e.g. a draft calling `memcpy` instead of `func_0012821C`) is not matched, even if `verify_fast.py` passes.

Never promote on a score-only improvement; archive instead. Record negative results (levers tried) in the draft's `STATUS:` header.

## 5. Security and legal considerations

- **Never modify the original ISO.** Work on copies in `extracted/` and `build/` only.
- **No copyrighted material in git:** ISO, extracted game data, original ELF/IRX/XFF binaries and build outputs stay in `.gitignore`. The repo holds only tooling, configs, hashes, notes, asm and C source. Check `git status` before every commit.
- **Downloads are untrusted:** the EE-GCC toolchains (`tools/cc/`, gitignored) and any fetched sources are third-party binaries; download only with user approval, keep them in their own directories, and don't run scripts from inside downloaded directories.
- **External sources** (Newlib mirrors, ps2sdk, other decomp projects) are corroborating evidence only; don't copy content that isn't permissively licensed, and never treat another region's project as an ABI authority for NTSC-U.
- **Secrets:** don't commit credentials or personal data beyond git authorship.
- **Irreversible/outward actions** (force-push, deleting branches, publishing artifacts, large downloads) require explicit user confirmation.

## 6. End-of-session checklist

1. Re-run the gates (`verify_fast.py`, `make check`) and confirm green.
2. Regenerate `docs/ledger.json`.
3. Add a session entry to `CONTEXT.md` (what changed, metrics, levers learned, next targets); keep this file stable.
4. Report to the user (in Portuguese): summary, verified hashes/percentages, TODO list, assumptions/uncertainties.
5. Commit docs changes separately (`docs: ...`).
