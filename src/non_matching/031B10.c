/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 23 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/031B10.s); this C
 * draft (Session 9) is kept for the record. */
struct P031B10 {                 /* the func_001271B0 part block */
    unsigned int type;           /* 0x00: 0/1 NaN, 2 zero, 3 normal, 4 inf */
    int sign;                    /* 0x04 */
    int exp;                     /* 0x08 */
    int pad0C;                   /* 0x0C */
    long long mant;              /* 0x10 */
};

extern void __unpack_d(long long *in, struct P031B10 *out);

int dptoli(long long x) {
    struct P031B10 out;
    int n;
    int v;

    __unpack_d(&x, &out);
    if (out.type == 2)
        return 0;
    if (out.type < 2u)
        return 0;
    if (out.type != 4) {
        n = out.exp;
        if (n < 0)
            return 0;
        if (n < 0x1F) {
            v = (int)(out.mant >> (0x3C - n));
            return out.sign != 0 ? -v : v;
        }
    }
    return out.sign != 0 ? (int)0x80000000 : 0x7FFFFFFF;
}
