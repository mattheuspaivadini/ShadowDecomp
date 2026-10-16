/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 24 [cc=296 -fno-optimize-sibling-calls].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/024B90.s); this C
 * draft (Session 9) is kept for the record. */
long long litodp(int x);
long long dpmul(long long a, long long b);
long long dpadd(long long a, long long b);
float dptofp(long long a);

float __floatdisf(long long x) {
    long long a;
    long long b;
    long long lo;

    if ((unsigned long long)(x + 0x1FFFFFFFFFFFFFLL) > 0x3FFFFFFFFFFFFEULL
        && (x & 0x7FF) != 0)
        x |= 0x800;
    a = litodp((int)(x >> 32));
    a = dpmul(a, 0x40F0000000000000LL);
    a = dpmul(a, 0x40F0000000000000LL);
    lo = (long long)(int)(x & 0xFFFFFFFF);
    b = litodp((int)lo);
    if (lo < 0)
        b = dpadd(b, 0x41F0000000000000LL);
    return dptofp(dpadd(a, b));
}
/* func_00124B90 */
