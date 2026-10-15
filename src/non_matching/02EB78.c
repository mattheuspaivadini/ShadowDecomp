/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 5 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02EB78.s); this C
 * draft (Session 9) is kept for the record. */
int func_0012EB78(unsigned int *p) {
    unsigned int x = *p;
    int n;

    if ((x & 7) != 0) {
        if (x & 1)
            return 0;
        if (x & 2) {
            *p = x >> 1;
            return 1;
        }
        *p = x >> 2;
        return 2;
    }
    n = 0;
    if ((x & 0xFFFF) == 0) {
        n = 0x10;
        x >>= 16;
    }
    if ((x & 0xFF) == 0) {
        n += 8;
        x >>= 8;
    }
    if ((x & 0xF) == 0) {
        n += 4;
        x >>= 4;
    }
    if ((x & 3) == 0) {
        n += 2;
        x >>= 2;
    }
    if (x & 1) {
        *p = x;
        return n;
    }
    x >>= 1;
    n += 1;
    if (x == 0)
        return 0x20;
    *p = x;
    return n;
}
