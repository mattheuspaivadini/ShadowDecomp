/* STATUS (10, 2026-10-16): NON_MATCHING. best score 7 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/026FA0.s); this C
 * draft (10) is kept for the record. */
extern double litodp(int a0);
extern double dpmul(double a0, double a1);
extern double dpadd(double a0, double a1);

double __floatdidf(long long a0) {
    int lo;
    int hi;
    double r;
    double d;

    hi = (int)(a0 >> 32);
    lo = (int)a0;
    r = dpmul(litodp(hi), 65536.0);
    r = dpmul(r, 65536.0);
    d = litodp(lo);
    if (lo < 0)
        d = dpadd(d, 4294967296.0);
    return dpadd(r, d);
}
/* __floatdidf */
