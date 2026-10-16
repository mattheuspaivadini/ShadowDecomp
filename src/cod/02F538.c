/* asm/cod/02F538.s -> _d2b.
 * Newlib mprec.c _d2b (Pack_32/IEEE_8087, !Sudden_Underflow)
 * MATCHED. */
union S02F538_double {
    double       d;
    unsigned int i[2];
};

#define word0(x) ((x).i[1])
#define word1(x) ((x).i[0])
#define d0 word0(d)
#define d1 word1(d)

#define Frac_mask 0xfffffu
#define Exp_shift 20
#define Exp_msk1  0x100000u
#define Bias      1023
#define P         53

struct S02F538_big {
    void         *next;     /* 0x00 */
    int           k;        /* 0x04 */
    int           maxwds;   /* 0x08 */
    int           sign;     /* 0x0C */
    int           wds;      /* 0x10 */
    unsigned int  x[1];     /* 0x14 */
};

extern struct S02F538_big *_Balloc(void *ptr, int k);
extern int _lo0bits(unsigned int *y);
extern int _hi0bits(unsigned int y);

struct S02F538_big *_d2b(void *ptr, double _d, int *e, int *bits)
{
    union S02F538_double d;
    struct S02F538_big *b;
    int de, i, k;
    unsigned int *x, y, z;

    d.d = _d;
    b = _Balloc(ptr, 1);
    x = b->x;

    z = d0 & Frac_mask;
    d0 &= 0x7fffffff;           /* clear sign bit, which we ignore */
    if ((de = (int)(d0 >> Exp_shift)) != 0)
        z |= Exp_msk1;

    if (d1) {
        y = d1;
        k = _lo0bits(&y);
        if (k) {
            x[0] = y | z << (32 - k);
            z >>= k;
        } else
            x[0] = y;
        i = b->wds = (x[1] = z) ? 2 : 1;
    } else {
        k = _lo0bits(&z);
        x[0] = z;
        i = b->wds = 1;
        k += 32;
    }

    if (de) {
        *e = de - Bias - (P - 1) + k;
        *bits = P - k;
    } else {
        *e = de - Bias - (P - 1) + 1 + k;
        *bits = 32 * i - _hi0bits(x[i - 1]);
    }
    return b;
}
