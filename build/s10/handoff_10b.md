# Session 10b handoff — hard cases (diff-driven)

**Matches gained: +1** (`028778`). **Totals: 344 / 1036 matched from C, 24,612 B = 12.083 % of .text**; HASH MATCH (`6f853f64…`), container byte-identical, `verify_c.py` 344/344. Commit `821adf9` (+ closing commit).
Ledger: 344 matched / 328 near / 191 asm-permanent / 173 untouched / 501 real pool.

| stem | before | after | iterations | best draft | residual hypothesis |
|------|--------|-------|-----------|------------|---------------------|
| 028778 | 1 (cc=296) | **0 MATCH** | 1 / 6 (Medium) | `src/cod/028778.c` | — (commutative `addu` operand order) |
| 022550 | 3 (cc=29) | 3 | 3 / 3 | `src/non_matching/022550.c` (variants in `build/s10/perm/022550/`) | register allocation only: `%hi(D_00135958)` pseudo and loaded value swap `$v0/$v1`, same schedule; probably a source shape that changes pseudo creation order (not store order, temps, volatile, struct, local extern or const-local base) |
| 0229B0 | 3 | 3 | 0 | `src/non_matching/0229B0.c` | not attempted — family stopped by rule (022550 did not improve) |
| 022A38 | 3 | 3 | 0 | `src/non_matching/022A38.c` | not attempted (same rule) |
| 022CE0 | 3 | 3 | 0 | `src/non_matching/022CE0.c` | not attempted (same rule) |

All scoring included the third-generation PE retry (`score_drafts.py` default `--extra-cc` = wine 2.95.3-136/-114/2.95.2-273a). No escalation to High reasoning was needed. No compiler flags changed.

**New pattern — commutative operand order:** when the only diff is one `addu rd,rs,rt` with rs/rt swapped, swap the C operands (`i*4 + base` ↔ `base + i*4`).
The permuter's body/decl-order mutations cannot produce this change, which is why 028778 was stuck at 1 after Session 10a.

New tool: `build/s10/pdiff.py <stem>` (side-by-side disassembled diff over `build/s10/perm/<stem>/*.c`). Notes: `build/s10/notes_10b.md`.
