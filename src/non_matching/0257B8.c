/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 19 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0257B8.s); this C
 * draft (Session 9) is kept for the record. */
struct B01257B8 {
    int       f00;      /* 0x00 kind: 3, or 2 for zero */
    int       f04;      /* 0x04 sign bit */
    int       f08;      /* 0x08 exponent countdown (0x3C) */
    int       pad0C;    /* 0x0C */
    long long v;        /* 0x10 magnitude */
};

long long func_001270D8(void *desc);

long long func_001257B8(int a0) {
    struct B01257B8 d;
    unsigned int sign;
    long long v;
    int n;

    d.f00 = 3;
    sign = (unsigned int)a0 >> 31;
    d.f04 = sign;
    if (a0 == 0) {
        d.f00 = 2;
    } else {
        d.f08 = 0x3C;
        if (sign == 0) {
            d.v = a0;
        } else {
            if (a0 == 0x80000000)
                return 0xC1E0000000000000LL;
            d.v = -a0;
        }
        v = d.v;
        if ((unsigned long long)v <= 0x0FFFFFFFFFFFFFFFULL) {
            n = d.f08;
            do {
                v = v << 1;
                n = n - 1;
            } while ((unsigned long long)v <= 0x0FFFFFFFFFFFFFFFULL);
            d.f08 = n;
            d.v = v;
        }
    }
    return func_001270D8(&d);
}
