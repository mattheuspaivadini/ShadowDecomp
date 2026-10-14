/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 17 [cc=29, default].
 * copy-in loop after record put.
 * The original .s stays in the build (asm/cod/019498.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/019498.s -> func_00119498 @ 0x00119498 (0x90 bytes, 36 insns)
 * func_00118380(a0, a4, p, 0, n * 4 + 4) (`sll $a4,$s0,2` + `addiu +4`); on
 * failure -0x21E, else copy the n words at p + 1 into dst with a down-counting
 * loop (`blezl` entry guard + `bnez` back-edge, `lw`/`sw` in the jal/branch
 * shadows) and return p[0] (the `blezl`'s delay slot holds that load).
 * MATCH GUESS: cc=29 (0191xx func_00118380 family) */
int func_00118380(int a0, int a1, int *p, int a3, int a4);

int func_00119498(int a0, int *p, int *dst, int n, int a4) {
    int *src;
    int r;

    r = func_00118380(a0, a4, p, 0, n * 4 + 4);
    if (r < 0)
        return -0x21E;
    src = p + 1;
    while (n > 0) {
        *dst++ = *src++;
        n--;
    }
    return p[0];
}
