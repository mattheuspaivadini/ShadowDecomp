/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 35 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/026800.s); this C
 * draft (Session 9) is kept for the record. */
struct S026800 {
    char pad00[0x8];
    long long f08;          /* 0x08 */
    long long f10;          /* 0x10 */
    char pad18[0x3E0];
    short f3F8;             /* 0x3F8 */
    char pad3FA[0x7D];
    char f477;              /* 0x477 */
};

extern unsigned char *func_00125998(unsigned char *p, int *out);
extern unsigned char *func_001259E0(unsigned char *p, int *out);
extern void func_00127448(void);

unsigned char *func_00126800(unsigned char *p, struct S026800 *s) {
    unsigned char c;
    int v;

    c = *p++;
    switch (c) {
    case 0x50 ... 0x6F:
        s->f3F8 = 0xFFB0 + c;
        break;
    case 0x90:
        p = func_001259E0(p, &v);
        s->f3F8 = v;
        /* falls through */
    case 0x70 ... 0x8F:
        s->f3F8 = 0xFF90 + c;
        p = func_001259E0(p, &v);
        s->f10 = v;
        break;
    case 0x92:
        p = func_001259E0(p, &v);
        s->f3F8 = v;
        p = func_001259E0(p, &v);
        s->f10 = v;
        break;
    case 6:
        s->f477 = 1;
        break;
    case 0x23:
        p = func_00125998(p, &v);
        s->f08 = v;
        break;
    default:
        func_00127448();
        break;
    }
    return p;
}
