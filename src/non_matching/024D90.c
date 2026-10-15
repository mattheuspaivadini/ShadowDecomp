/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 41 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/024D90.s); this C
 * draft (Session 9) is kept for the record. */
extern int func_00125768(long long a0, long long a1);
extern long long func_001253A0(long long a0, long long a1);
extern long long func_001252E0(long long a0, long long a1);
extern long long func_00125338(long long a0, long long a1);
extern int func_001258F8(long long a0);
extern long long func_00126FA0(long long a0);
extern long long func_00125040(float x);

long long func_00124D90(float x) {
    unsigned long long s0;
    long long s1;
    long long d;
    long long w;
    int t;

    s1 = func_00125040(x);
    if (func_00125768(s1, 0) < 0)
        return 0;
    t = func_001258F8(func_001253A0(s1, 0x3DF0000000000000LL));
    s0 = (unsigned long long)t << 32;
    if (s0 & 0x8000000000000000ULL) {
        w = func_00126FA0((s0 & 1) | (s0 >> 1));
        d = func_001252E0(w, w);
    } else {
        d = func_00126FA0(s0);
    }
    s1 = func_00125338(s1, d);
    if (func_00125768(s1, 0) >= 0)
        s0 = s0 + (unsigned long long)func_001258F8(s1);
    else
        s0 = s0 - (unsigned long long)func_001258F8(func_00125338(0, s1));
    return s0;
}
