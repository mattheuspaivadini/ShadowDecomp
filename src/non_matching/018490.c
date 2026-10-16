/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 10 [cc=29].
 * func_00118490: sll a3, 2 and caller register forwarding upfront
 * The original .s stays in the build (asm/cod/018490.s); this C
 * draft (Session 12) is kept for the record. */
int func_0012821C(int dst, int src, int n);

int func_00118490(int *p, int a1, int a2, int a3, int a4) {
    int lim;

    a3 <<= 2;
    if (a1 == 0)
        return 0;
    lim = p[12] - a3;
    if (a4 < 0 || lim < a4)
        return -0x21F;
    func_0012821C(a1, a2 + a3, a4);
    return 0;
}
