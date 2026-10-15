/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 40 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02F2D0.s); this C
 * draft (Session 9) is kept for the record. */
long long func_0012F2D0(long long x, long long y) {
    int e;
    int n;
    long long v;

    e = (int)(x >> 32) & 0x7FF00000;
    e = e + 0xFCC00000;
    n = -e;
    if (e > 0) {
        v = (y & 0xFFFFFFFFLL) | ((long long)e << 32);
        return v & 0xFFFFFFFF00000000LL;
    }
    n = n >> 20;
    if (n < 0x14) {
        v = (y & 0xFFFFFFFFLL) | ((long long)(0x80000 >> n) << 32);
        return v & 0xFFFFFFFF00000000LL;
    }
    n = n - 0x14;
    if (n < 0x1F)
        v = 1 << (31 - n);
    else
        v = 1;
    return ((y & 0xFFFFFFFFLL) & 0xFFFFFFFF00000000LL) | ((v << 32) >> 32);
}
