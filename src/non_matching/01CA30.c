/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 7 [cc=29].
 * goto-entered do/while reproduces the loop rotation; residual = placement of the err-return block (b/daddu emitted before the increment block)
 * The original .s stays in the build (asm/cod/01CA30.s); this C
 * draft (Session 23) is kept for the record. */
int func_0011C4C8(int a0, unsigned int a1, int *err);
int func_0011CA30(int a0, unsigned int a1) {
    int err;
    int n;
    if (a1 == 0xFFFFFFFFU) return 0;
    n = 1;
    goto start;
    do {
        n++;
        a1 &= 0x7FFFFFFF;
    start:
        a1 = func_0011C4C8(a0, a1, &err);
        if (err) return err;
        if (a1 == 0xFFFFFFFFU) return n;
    } while ((int)a1 < 0);
    return 0x81019002;
}
