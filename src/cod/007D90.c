/* asm/cod/007D90.s -> func_00107D90.
 * fixed-point mantissa of a double bit pattern, capped at 9999 (%e helper; the caller passes (unsigned long)(d * 1e6)); the raw bits and the mantissa share one variable (Session 44)
 * MATCHED. */
int func_00107D90(unsigned long u) {
    long e;

    e = (u << 1) >> 53;
    e -= 0x433;
    if (e < -53)
        return 0;
    if (e >= 13)
        return 9999;
    u = (u << 12) >> 12;
    u |= 1UL << 52;
    if (e < 0) {
        e = -e;
        u >>= (int)(e - 2);
        if ((u & 3) == 3)
            u = (u >> 2) + 1;
        else
            u >>= 2;
    } else {
        u <<= (int)e;
    }
    return (int)u;
}
