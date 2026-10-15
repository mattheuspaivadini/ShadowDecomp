/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 30 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0271B0.s); this C
 * draft (Session 9) is kept for the record. */
struct D25768 {
    int type;                       /* 0x00 */
    int sign;                       /* 0x04 */
    int exp;                        /* 0x08 */
    int pad0C;                      /* 0x0C */
    unsigned long long mant;        /* 0x10 */
    unsigned long long pad18;       /* 0x18 */
};

void func_001271B0(long long *in, struct D25768 *z) {
    unsigned long long v = (unsigned long long)*in;
    unsigned long long mant = v & 0x000FFFFFFFFFFFFFULL;
    int exp = (int)((v >> 52) & 0x7FF);
    int sign = (int)(v >> 63);

    z->sign = sign;
    if (exp == 0) {
        z->type = 2;
        return;
    }
    if (exp == 0x7FF) {
        z->exp = 0x3FF;
        if (mant == 0) {
            z->mant = 0x1000000000000000ULL;
            z->type = 4;
            return;
        }
        z->type = (mant << 8) & 0x0008000000000000ULL ? 1 : 0;
        z->mant = mant << 8;
        return;
    }
    z->mant = (mant << 8) | 0x1000000000000000ULL;
    z->exp = exp - 0x3FF;
    z->type = 3;
}
