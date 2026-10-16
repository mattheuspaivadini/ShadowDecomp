/* STATUS (Session 8, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * scheduling of bounded memcpy check
 * The original .s stays in the build (asm/cod/018438.s); this C
 * draft (Session 8) is kept for the record. */
void *func_0012821C(void *dst, const void *src, int n);

int func_00118438(int *p, char *a1, int a2, const void *a3, int a4) {
    int lim = p[12] - (a2 << 2);

    if (a3 != 0) {
        if (a4 < 0 || lim < a4)
            return -0x21F;
        func_0012821C(a1 + (a2 << 2), a3, a4);
    }
    return 0;
}
