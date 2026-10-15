# Session 10b notes

Helper: `build/s10/pdiff.py <stem>` (permute.py on build/s10/perm/<stem>/, side-by-side diff). Staging is slow (~4 min/run) -> batch variants per run.

## 028778 (start score 1, cc=296)
- Diff: single insn `addu $a0,$v0,$v1` (orig) vs `addu $a0,$v1,$v0` (mine). Class: **operand order of a commutative add (register allocation/canonical operand order)**, not scheduling.
- It1: swap operands `index*4 + base`, pointer arith, &arr[idx], temp off, unsigned.
- RESULT: `index * 4 + ctx[0x75]` (and temp/unsigned forms) = MATCH cc=296. Promoted; gate HASH MATCH, container identical, 344/344. Commit 821adf9.

## 022550 (start score 3, cc=29)
- Diff: `lui $v1,%hi(D_00135958); lw $v0,%lo($v1); sw $v0,4($s0)` (orig) vs `$v0`/`$v1` swapped (mine). Same schedule. Class: **register allocation (v0/v1 swap of the hi-pseudo vs the loaded value)**.
- It1: scalar extern (4), tmp before/after 0xC store, store order swap, ptr local, const-local ptr (14), unsigned -> all 3.
- It2: user var v before stores, const-local n=2, char[] cast, hdr int* (10) -> all 3.
- It3: volatile, struct field (4), local extern, char *buf const-local (10 / 3 when assigned after the call) -> all 3.
- STOP command family (rule): 0229B0/022A38/022CE0 untouched.
