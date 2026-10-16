/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 11 [cc=296].
 * isinf: fdlibm register swap v0/v1 on (lx|-lx)>>31 sign-bit extraction
 * The original .s stays in the build (asm/cod/02F9B8.s); this C
 * draft (Session 12) is kept for the record. */
int isinf(long long x) {
    int hx, lx;
    lx = (int)x;
    hx = (int)(x >> 32);
    hx &= 0x7fffffff;
    hx |= (unsigned int)(lx | -lx) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (int)((unsigned int)(hx | -hx) >> 31);
}
