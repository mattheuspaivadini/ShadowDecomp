/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 27 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/027390.s); this C
 * draft (Session 9) is kept for the record. */
union F32_27390 {
    unsigned int w;
    float f;
};

float func_00127390(int *p, int a1, unsigned int bits) {
    int type = p[0];
    int mant = p[3];
    int sign = p[1];
    int e;
    union F32_27390 u;

    e = 0;
    if (type == 2) {
        mant = 0;
    } else if (mant != 0) {
        int exp = p[2];

        if (exp < -0x7E) {
            mant = 0;
        } else if (exp >= 0x81) {
            e = 0xFF;
            mant = 0;
        } else {
            e = exp + 0x7F;
            if (exp == 0x80 && mant < 0) {
                e = 0xFF;
                mant = 0;
            } else {
                mant = (int)((unsigned int)mant >> 7);
            }
        }
    } else {
        mant = 0;
    }
    u.w = bits;
    u.w = (u.w & 0xFF800000) | ((unsigned int)mant & 0x7FFFFF);
    u.w = (u.w & 0x807FFFFF) | (((unsigned int)e & 0xFF) << 23);
    u.w = (u.w & 0x7FFFFFFF) | ((unsigned int)sign << 31);
    return u.f;
}
