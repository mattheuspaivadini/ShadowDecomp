/* STATUS (Session 22, 2026-10-17): NON_MATCHING. best score 9 [cc=ee-gcc2.9-991111-01-dtls13010 -g0].
 * dtls13010 -g0 fills the jr slot; residual = the param copy into a1 and the a1/a2 roles of mantissa/exponent
 * The original .s stays in the build (asm/cod/007D90.s); this C
 * draft (Session 22) is kept for the record. */
int func_00107D90(double x) {
    union { double d; unsigned long u; } c;
    long e;
    unsigned long m;

    c.d = x;
    e = (long)((c.u << 1) >> 53) - 0x433;
    if (e < -53)
        return 0;
    if (e >= 13)
        return 9999;
    m = ((c.u << 12) >> 12) | (1UL << 52);
    if (e < 0) {
        e = -e;
        m >>= (int)(e - 2);
        if ((m & 3) == 3)
            m = (m >> 2) + 1;
        else
            m >>= 2;
    } else {
        m <<= (int)e;
    }
    return (int)m;
}
