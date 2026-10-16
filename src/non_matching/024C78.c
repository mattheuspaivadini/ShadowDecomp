/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 48 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/024C78.s); this C
 * draft (Session 9) is kept for the record. */
extern int dpcmp(long long a0, long long a1);
extern long long dpmul(long long a0, long long a1);
extern long long dpadd(long long a0, long long a1);
extern long long dpsub(long long a0, long long a1);
extern int dptoul(long long a0);
extern long long __floatdidf(long long a0);

long long __fixunsdfdi(long long a0) {
    unsigned long long s0;
    long long s1;
    long long d;
    long long w;
    int t;

    if (dpcmp(a0, 0) < 0)
        return 0;
    t = dptoul(dpmul(a0, 0x3DF0000000000000LL));
    s0 = (unsigned long long)t << 32;
    if (s0 & 0x8000000000000000ULL) {
        w = __floatdidf((s0 & 1) | (s0 >> 1));
        d = dpadd(w, w);
    } else {
        d = __floatdidf(s0);
    }
    s1 = dpsub(a0, d);
    if (dpcmp(s1, 0) >= 0)
        s0 = s0 + (unsigned long long)dptoul(s1);
    else
        s0 = s0 - (unsigned long long)dptoul(dpsub(0, s1));
    return s0;
}
/* func_00124C78 */
