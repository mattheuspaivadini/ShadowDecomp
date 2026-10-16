/* STATUS (Session 8, 2026-10-16): NON_MATCHING. best score 12 [cc=29].
 * movz vs movn in soft-fp dptofp
 * The original .s stays in the build (asm/cod/0258A0.s); this C
 * draft (Session 8) is kept for the record. */
struct D25768 {
    int type;
    int sign;
    int exp;
    int pad0C;
    long long mant;
    long long pad18;
};

int __unpack_d(long long *in, struct D25768 *out);
int __make_fp(int a0, int a1, int a2, int a3);

int dptofp(long long a0) {
    struct D25768 pa;
    int v;
    int a3;

    __unpack_d(&a0, &pa);
    v = (int)((pa.mant << 2) >> 32);
    a3 = v | 1;
    if ((pa.mant & 0x3FFFFFFF) == 0)
        a3 = v;
    return __make_fp(pa.type, pa.sign, pa.exp, a3);
}
