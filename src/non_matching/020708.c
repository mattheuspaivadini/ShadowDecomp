/* STATUS (Session 6, step 3): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * The corrected struct (0x184 stride, field +0x2A) reproduces the right
 * instructions (addiu 0x184 / mult / lhu 0x2A / two mults) but the
 * register roles differ (original: stride+base in $v1, w in $a4; ours:
 * $t0/$v0/$v1). Score 8 instructions at cc=29 (old-struct variant: 5,
 * coincidental). 10 expression-shape variants tried; all >=5.
 * See docs/non-matching-backlog.md. */
 *
 * Look up the record at `index` (stride 0x184), read the unsigned short at
 * +0x2A and forward func_00121A70(index, a1, a2 * w, a3 * w). The two scaled
 * arguments are computed with the R5900 `mult $zero,rs,rt` + `mflo` shape
 * (the 2.9 generation emits the 3-operand mult for a runtime multiplier).
 *
 * MATCHED (Session 6, step 3) with cc=29. The record struct MUST model the
 * 0x184 stride (`char rest[0x184 - 0x2C]`) - with a bare
 * `{ char pad00[0x2A]; unsigned short w; }` the compiler uses 0x2C as the
 * stride and the field offset collapses to 0.
 */
struct R020708 {
    char pad00[0x2A];
    unsigned short w;            /* 0x2A */
    char rest[0x184 - 0x2C];     /* stride 0x184 */
};

extern struct R020708 D_00135638[];

int func_00121A70(int a0, int a1, int a2, int a3);

int func_00120708(int index, int a1, int a2, int a3) {
    unsigned short w = D_00135638[index].w;

    return func_00121A70(index, a1, a2 * w, a3 * w);
}
