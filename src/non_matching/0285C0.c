/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 21 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0285C0.s); this C
 * draft (Session 9) is kept for the record. */
extern int _impure_ptr[];         /* .data 0x00135C60: lui/%lo (non-small) */
extern int func_00129930(int a0, int a1, int a2);

int func_001285C0(char *fmt, ...) {
    int f;
    int ap;

    ap = (int)__builtin_saveregs();
    f = _impure_ptr[0];
    *(int *)(*(int *)(f + 8) + 0x54) = f;
    return func_00129930(*(int *)(f + 8), (int)fmt, ap);
}
