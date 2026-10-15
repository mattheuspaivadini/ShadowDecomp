/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 31 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0270D8.s); this C
 * draft (Session 9) is kept for the record. */
struct D25768 {
    unsigned int       type;    /* 0x00 */
    int                sign;    /* 0x04 */
    int                exp;     /* 0x08 */
    int                pad0C;   /* 0x0C */
    unsigned long long mant;    /* 0x10 */
};

long long func_001270D8(struct D25768 *b, int unused, long long src) {
    unsigned int       t;
    unsigned long long m;
    int                e;

    t = b->type;
    e = 0;
    m = b->mant;
    if (t < 2) {
        m |= 0x0008000000000000ULL;
        e = 0x7FF;
    } else if (t == 4) {
        e = 0x7FF;
        m = 0;
    } else if (t == 2) {
        m = 0;
    } else if (m != 0) {
        if (b->exp < -0x3FE) {
            m = 0;
        } else if (b->exp < 0x400) {
            e = b->exp + 0x3FF;
            m = m >> 8;
        } else {
            e = 0x7FF;
            m = 0;
        }
    }
    src = (src & 0xFFF0000000000000LL)
        | (long long)(m & 0x000FFFFFFFFFFFFFULL);
    src = (src & 0x800FFFFFFFFFFFFFLL) | ((long long)(e & 0x7FF) << 52);
    src = (src & 0x7FFFFFFFFFFFFFFFLL) | ((long long)b->sign << 63);
    return src;
}
