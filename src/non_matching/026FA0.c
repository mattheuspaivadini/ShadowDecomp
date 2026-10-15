/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 7 [cc=296 -fno-optimize-sibling-calls].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/026FA0.s); this C
 * draft (Session 9) is kept for the record. */
extern double func_001257B8(int a0);
extern double func_001253A0(double a0, double a1);
extern double func_001252E0(double a0, double a1);

double func_00126FA0(long long a0) {
    int lo;
    int hi;
    double r;
    double d;

    hi = (int)(a0 >> 32);
    lo = (int)a0;
    r = func_001253A0(func_001257B8(hi), 65536.0);
    r = func_001253A0(r, 65536.0);
    d = func_001257B8(lo);
    if (lo < 0)
        d = func_001252E0(d, 4294967296.0);
    return func_001252E0(r, d);
}
