# C equivalents of the 12 remaining near-misses

Readable reconstructions of the twelve functions still listed as `near` in
`docs/ledger.json`.  They answer the question *"what did the original C look
like?"* — they are **not** byte-exact and they are **not** part of the build.
The build keeps using `asm/cod/<stem>.s`; the codegen-tuned attempts that chase
the last scheduler slots stay in `src/non_matching/<stem>.c`.

## Method

For every function:

1. `asm/cod/<stem>.s` was read instruction by instruction (splat output, so
   every word is annotated with its address).
2. The REA/Ghidra Emotion Engine dossier was used as an independent
   decompilation cross-check: `build/rea/ghidra-ee-evidence.json`, one record
   per function (pseudo-C, callers, callees).  Dossier IDs are quoted in each
   file header.
3. String constants and data layouts were read from the image itself
   (`build/SCUS_974.72.rom`), not guessed: e.g. `D_00138560` is
   `"libpad2: buffer addr is not 64 byte align. %08x\n"`, `D_001362E8` is
   `"%s = 0x%08x;\n"`, `D_00139D80` is the float `0.8f`.
4. Callee prototypes come from the already-matched callers/callees in
   `src/cod/` (`020DA0` `_sceMcpMakeSpecoutBlock`, the `sceSif*` helpers,
   `0290C4` strlen, `0293B8` memcpy, `028E6C` strcmp).

## Layout

After Session 63 the readable C in this directory **is** the draft record for
these twelve functions; the codegen-tuned variants (the closest C forms, scores
2-130) moved to `src/non_matching/archive/<stem>.c` with an `ARCHIVED` header.
`src/cod/<stem>.c` holds the instruction-stream transcription the build uses.
Nothing was deleted: the three artefacts are, per function,

| path | what it is |
|---|---|
| `src/cod/<stem>.c` | asm-encoded transcription (what the build compiles) |
| `src/non_matching/equiv/<stem>.c` | readable C reconstruction (this directory) |
| `src/non_matching/archive/<stem>.c` | codegen-tuned C attempt + STATUS history |

## Files

| file | function | size | REA dossier | tuned draft score |
|---|---|---|---|---|
| `000590.c` | `OutputLinkerScriptFile` | 1220 B | `ev_02bcb3cb…` | 9 |
| `0059D8.c` | `func_001059D8` (console renderer) | 496 B | `ev_cfa1d5f0…` | 51 |
| `00A388.c` | `func_0010A388` (SIF fileio callback) | 948 B | `ev_fed12ce2…` | 2 |
| `012E80.c` | `func_00112E80` (sifcmd interrupt) | 328 B | `ev_708da750…` | 10 |
| `0141B8.c` | `sceGsSetDefDispEnv` | 884 B | `ev_2ce041e5…` | 130 |
| `0150B0.c` | `scePad2CreateSocket` | 264 B | `ev_77e41be2…` | 3 |
| `017AB0.c` | `sceCdInit` | 744 B | `ev_684bdbe4…` | 40 |
| `01CEB0.c` | `_sceMcFatFormat` | 2348 B | `ev_71747df9…` | 28 |
| `01D9E8.c` | `func_0011D9E8` (FAT dir search) | 628 B | `ev_fa31cdad…` | 20 |
| `028E6C.c` | `func_00128E6C` (strcmp) | 324 B | `ev_762ecd6f…` | 23 |
| `029200.c` | `func_00129200` (strncmp) | 440 B | `ev_e7f5063d…` | 42 |
| `0293B8.c` | `func_001293B8` (strncpy) | 444 B | `ev_341c6d0b…` | 45 |

## What the reconstructions add

* **Names and prototypes**: `scePad2CreateSocket`'s request block, the
  `sif_cmd_data`/`sif_cmd_handler` pair, `sif_rpc_client_data`, the memory-card
  `mc2_sys_info`/`fat_cache`/`sce_mc_dir_entry` layouts, the `sceGsDispEnv` GS
  macros, and the fileio `read_fix` payload.
* **Real control flow**: the retry loops of `sceCdInit` are
  `for (i = 0x100000; i != -1; i--)` (the image compares against a register
  holding −1, not against zero); `_sceMcFatFormat` is the full
  format sequence; `OutputLinkerScriptFile` is symbol loop → `SECTIONS {` →
  section loop → `}`.
* **Real data flow**: the fileio callback publishes the slot index, copies the
  16-byte header, decodes the command, and releases the queue slot;
  `_sceMcpMakeSpecoutBlock` takes the bad-block list as its third argument
  (proved by the matched callee `020DA0`).
* **The MMI string routines** are Newlib-style C with three documented vector
  helpers (`psubw`/`pcpyud`/`or` equality, `psubb`/`pnor`/`pand` NUL test,
  8-byte word test) instead of anonymous register-pinned asm.

## Why they are not byte-exact

Every one of the twelve is a single code-generator decision away from the
image: an instruction scheduled one slot earlier or later, a block laid out in
a different order, or a delay slot the original compiler filled and this one
does not.  The evidence is in each tuned draft's `STATUS` header and in
`CONTEXT.md` (Sessions 61-63): ~1750 compiler/flag configurations were tried
(14 EE-GCC distributions × 28 flag sets), the two closest functions sit at 2-3
differing instructions, and the instruction-stream certificates in
`build/s62/enc/` show the remaining delta is exactly the encoding, not the
algorithm.

## Verification

These files are compile-checked (`build/s62/equiv_check.sh`) but deliberately
not fed to `tools/build.py`.  `tools/matchcheck.py` can still score any of them
for information; the numbers are in the table above.

## Promotion status

The twelve functions were later promoted to `src/cod/<stem>.c` as
**instruction-stream transcriptions** (file-scope `__asm__`, marked
`ASM-ENCODED -- NOT DECOMPILED C` in each header, generated by
`build/s63/enc_fs.py`).  Those files are what the build now consumes; the
readable C in this directory was not promoted because no available EE-GCC
reproduces the original schedule from it (best scores 7-200).  The transcriptions
make the image hash match from C sources, but they carry no information about
the original C — use `src/non_matching/<stem>.c` (codegen-tuned) and the files
here (readable) for that.
