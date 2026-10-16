/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 18 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0258F8.s); this C
 * draft (Session 9) is kept for the record. */
struct D25768 {
    unsigned int type;              /* 0x00 */
    int sign;                       /* 0x04 */
    int exp;                        /* 0x08 */
    int pad0C;                      /* 0x0C */
    unsigned long long mant;        /* 0x10 */
    unsigned long long pad18;       /* 0x18 */
};

int __unpack_d(long long *in, struct D25768 *out);

int dptoul(long long a0) {
    struct D25768 pa;

    __unpack_d(&a0, &pa);
    if (pa.type == 2)
        return 0;
    if (pa.type < 2)
        return 0;
    if (pa.sign != 0)
        return 0;
    if (pa.type == 4)
        return -1;
    if (pa.exp < 0)
        return 0;
    if (pa.exp >= 0x20)
        return -1;
    if (pa.exp < 0x3D)
        return (int)(pa.mant >> (0x3C - pa.exp));
    return (int)(pa.mant << (pa.exp - 0x3C));
}
/* func_001258F8 */
