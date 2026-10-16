/* asm/cod/02EF80.s -> _lshift.
 * Newlib mprec.c _lshift (Pack_32); authentic source, Bigint offsets confirmed by matched _Balloc
 * MATCHED. */
struct S02EF80 {
    void         *next;     /* 0x00 */
    int           k;        /* 0x04 */
    int           maxwds;   /* 0x08 */
    int           sign;     /* 0x0C */
    int           wds;      /* 0x10 */
    unsigned int  x[1];     /* 0x14 */
};

extern struct S02EF80 *_Balloc(void *ptr, int k);
extern void _Bfree(void *ptr, struct S02EF80 *b);

struct S02EF80 *_lshift(void *ptr, struct S02EF80 *b, int k)
{
    int i, k1, n, n1;
    struct S02EF80 *b1;
    unsigned int *x, *x1, *xe, z;

    n = k >> 5;
    k1 = b->k;
    n1 = n + b->wds + 1;
    for (i = b->maxwds; n1 > i; i <<= 1)
        k1++;
    b1 = _Balloc(ptr, k1);
    x1 = b1->x;
    for (i = 0; i < n; i++)
        *x1++ = 0;
    x = b->x;
    xe = x + b->wds;
    if ((k &= 0x1f) != 0) {
        k1 = 32 - k;
        z = 0;
        do {
            *x1++ = (*x << k) | z;
            z = *x++ >> k1;
        } while (x < xe);
        if ((*x1 = z) != 0)
            ++n1;
    } else
        do
            *x1++ = *x++;
        while (x < xe);
    b1->wds = n1 - 1;
    _Bfree(ptr, b);
    return b1;
}
