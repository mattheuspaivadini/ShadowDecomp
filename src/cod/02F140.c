/* asm/cod/02F140.s -> __mdiff.
 * Newlib mprec.c __mdiff (Pack_32); 16-bit limb Storeinc loops
 * MATCHED. */
typedef unsigned int _ULong_02F140;   /* __ULong (32-bit on the EE) */
typedef int          _Long_02F140;    /* __Long  (signed shifts)    */

#define Storeinc(a, b, c)                     \
    (((unsigned short *)(a))[1] = (unsigned short)(b), \
     ((unsigned short *)(a))[0] = (unsigned short)(c), (a)++)

struct S02F140_big {
    struct S02F140_big *next;   /* 0x00 */
    int                 k;      /* 0x04 */
    int                 maxwds; /* 0x08 */
    int                 sign;   /* 0x0C */
    int                 wds;    /* 0x10 */
    _ULong_02F140      x[1];    /* 0x14 */
};

extern struct S02F140_big *_Balloc(void *ptr, int k);
extern int __mcmp(struct S02F140_big *a, struct S02F140_big *b);

struct S02F140_big *__mdiff(void *ptr, struct S02F140_big *a,
                            struct S02F140_big *b)
{
    struct S02F140_big *c;
    int i, wa, wb;
    _Long_02F140 borrow, y;
    _ULong_02F140 *xa, *xae, *xb, *xbe, *xc;
    _Long_02F140 z;

    i = __mcmp(a, b);
    if (!i) {
        c = _Balloc(ptr, 0);
        c->wds = 1;
        c->x[0] = 0;
        return c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    } else
        i = 0;
    c = _Balloc(ptr, a->k);
    c->sign = i;
    wa = a->wds;
    xa = a->x;
    xae = xa + wa;
    wb = b->wds;
    xb = b->x;
    xbe = xb + wb;
    xc = c->x;
    borrow = 0;
    do {
        y = (*xa & 0xffff) - (*xb & 0xffff) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) - (*xb++ >> 16) + borrow;
        borrow = z >> 16;
        Storeinc(xc, z, y);
    } while (xb < xbe);
    while (xa < xae) {
        y = (*xa & 0xffff) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) + borrow;
        borrow = z >> 16;
        Storeinc(xc, z, y);
    }
    while (!*--xc)
        wa--;
    c->wds = wa;
    return c;
}
