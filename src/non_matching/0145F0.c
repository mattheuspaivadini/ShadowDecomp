/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 35 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0145F0.s); this C
 * draft (Session 9) is kept for the record. */
struct S133970B {
    unsigned long long word00;      /* 0x00 */
};

void *func_00113520(void);

short func_001145F0(short a0, short a1, short a2) {
    int h = a1;
    int m = a0;
    int w = a2;
    struct S133970B *p = (struct S133970B *)func_00113520();
    int t;
    int u;
    int prod;

    t = h + 0x3F;
    h = (t >= 0) ? t : (h + 0x7E);
    h >>= 6;
    if (m & 2) {
        t = w + 0x3F;
        u = (t >= 0) ? t : (w + 0x7E);
        u >>= 6;
    } else {
        t = w + 0x1F;
        u = (t >= 0) ? t : (w + 0x3E);
        u >>= 5;
    }
    prod = h * u;
    if ((p->word00 & 0x0000FFFF0000FFFFULL) != 1)
        return (short)(prod * 2);
    return (short)prod;
}
