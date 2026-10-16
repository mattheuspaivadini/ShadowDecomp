/* asm/cod/02F3A0.s -> _b2d.
 * Newlib mprec.c _b2d (Pack_32/IEEE_8087), double_union word0/word1
 * MATCHED. */
union S02F3A0_double {
    double       d;
    unsigned int i[2];
};

#define word0(x) ((x).i[1])
#define word1(x) ((x).i[0])

#define Ebits 11
#define Exp_1 0x3ff00000u

struct S02F3A0_big {
    void         *next;     /* 0x00 */
    int           k;        /* 0x04 */
    int           maxwds;   /* 0x08 */
    int           sign;     /* 0x0C */
    int           wds;      /* 0x10 */
    unsigned int  x[1];     /* 0x14 */
};

extern int _hi0bits(unsigned int y);

double _b2d(struct S02F3A0_big *a, int *e)
{
    unsigned int *xa, *xa0, w, y, z;
    int k;
    union S02F3A0_double d;

    xa0 = a->x;
    xa = xa0 + a->wds;
    y = *--xa;
    k = _hi0bits(y);
    *e = 32 - k;
    if (k < Ebits) {
        word0(d) = Exp_1 | y >> (Ebits - k);
        w = xa > xa0 ? *--xa : 0;
        word1(d) = (y << ((32 - Ebits) + k)) | (w >> (Ebits - k));
        goto ret_d;
    }
    z = xa > xa0 ? *--xa : 0;
    if ((k -= Ebits) != 0) {
        word0(d) = Exp_1 | (y << k) | (z >> (32 - k));
        y = xa > xa0 ? *--xa : 0;
        word1(d) = (z << k) | (y >> (32 - k));
    } else {
        word0(d) = Exp_1 | y;
        word1(d) = z;
    }
ret_d:
    return d.d;
}
