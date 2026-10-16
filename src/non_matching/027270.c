/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 38 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/027270.s); this C
 * draft (Session 9) is kept for the record. */
struct R027270 {
    unsigned int       type;    /* 0x00 */
    int                sign;    /* 0x04 */
    int                exp;     /* 0x08 */
    int                pad0C;   /* 0x0C */
    unsigned long long mant;    /* 0x10 */
    unsigned long long pad18;   /* 0x18 */
};

int __fpcmp_parts_d(struct R027270 *a, struct R027270 *b) {
    if (a->type < 2 || b->type < 2)
        return 1;
    if (a->type == 4) {
        if (b->type == 4)
            return b->sign - a->sign;
        return a->sign == 0 ? 1 : -1;
    }
    if (b->type == 4)
        return b->sign == 0 ? -1 : 1;
    if (a->type == 2) {
        if (b->type == 2)
            return 0;
        return b->sign != 0 ? 1 : -1;
    }
    if (b->type == 2)
        return a->sign == 0 ? 1 : -1;
    if (a->sign != b->sign)
        return a->sign == 0 ? 1 : -1;
    if (b->exp < a->exp)
        return a->sign == 0 ? 1 : -1;
    if (a->exp < b->exp)
        return a->sign == 0 ? -1 : 1;
    if (b->mant < a->mant)
        return a->sign == 0 ? 1 : -1;
    if (a->mant < b->mant)
        return a->sign == 0 ? -1 : 1;
    return 0;
}
/* func_00127270 */
