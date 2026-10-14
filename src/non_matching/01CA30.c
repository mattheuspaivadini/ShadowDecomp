/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 32 [cc=29, default].
 * retry loop around func_0011C4C8.
 * The original .s stays in the build (asm/cod/01CA30.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/01CA30.s -> func_0011CA30 @ 0x0011CA30 (0x90 bytes, 36 insns)
 * Unwrap a chained error code: a1 == -1 (0xFFFFFFFF) returns 0 immediately;
 * otherwise loop { r = func_0011C4C8(a0, a1, &v1);
 *                   if (v1 != 0) return v1;
 *                   if (r == -1) return n;          (n counts the unwraps,
 *                                                    starting at 1)
 *                   if (r >= 0) return 0x81019002;  (the fix-up code)
 *                   n++; a1 &= 0x7FFFFFFF; }        (drop the top bit)
 * The `-1` is materialised with `lui`+`ori` twice (the guard and the `r == -1`
 * test), the mask is `lui 0x7FFF` + `ori 0xFFFF` + `and`, and the `s0 = 1`
 * initialiser sits in the `b` delay slot of the `a1 == -1` guard.
 * MATCH GUESS: cc=29 (01C1xx error-code family; the matched 01C4C8.c) */
int func_0011C4C8(int a0, int a1, int *a2);

int func_0011CA30(int a0, int a1) {
    int v1;
    int r;
    int n;

    if (a1 == -1)
        return 0;
    for (n = 1; ; n++) {
        r = func_0011C4C8(a0, a1, &v1);
        if (v1 != 0)
            return v1;
        if (r == -1)
            return n;
        if (r >= 0)
            return 0x81019002;
        a1 = a1 & 0x7FFFFFFF;
    }
}
