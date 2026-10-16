/* asm/cod/02EC70.s -> _multiply.
 * Newlib mprec.c mult (Pack_32); official name _multiply
 * MATCHED. */
typedef unsigned int _ULong_02EC70;

#define Storeinc(a, b, c)                     \
    (((unsigned short *)(a))[1] = (unsigned short)(b), \
     ((unsigned short *)(a))[0] = (unsigned short)(c), (a)++)

struct S02EC70_big {
    struct S02EC70_big *next;   /* 0x00 */
    int                 k;      /* 0x04 */
    int                 maxwds; /* 0x08 */
    int                 sign;   /* 0x0C */
    int                 wds;    /* 0x10 */
    _ULong_02EC70      x[1];    /* 0x14 */
};

extern struct S02EC70_big *_Balloc(void *ptr, int k);

struct S02EC70_big *_multiply(void *ptr, struct S02EC70_big *a,
                              struct S02EC70_big *b)
{
    struct S02EC70_big *c;
    int k, wa, wb, wc;
    _ULong_02EC70 carry, y, z;
    _ULong_02EC70 *x, *xa, *xae, *xb, *xbe, *xc, *xc0;
    _ULong_02EC70 z2;

    if (a->wds < b->wds) {
        c = a;
        a = b;
        b = c;
    }
    k = a->k;
    wa = a->wds;
    wb = b->wds;
    wc = wa + wb;
    if (wc > a->maxwds)
        k++;
    c = _Balloc(ptr, k);
    for (x = c->x, xa = x + wc; x < xa; x++)
        *x = 0;
    xa = a->x;
    xae = xa + wa;
    xb = b->x;
    xbe = xb + wb;
    xc0 = c->x;
    for (; xb < xbe; xb++, xc0++) {
        if ((y = *xb & 0xffff) != 0) {
            x = xa;
            xc = xc0;
            carry = 0;
            do {
                z = (*x & 0xffff) * y + (*xc & 0xffff) + carry;
                carry = z >> 16;
                z2 = (*x++ >> 16) * y + (*xc >> 16) + carry;
                carry = z2 >> 16;
                Storeinc(xc, z2, z);
            } while (x < xae);
            *xc = carry;
        }
        if ((y = *xb >> 16) != 0) {
            x = xa;
            xc = xc0;
            carry = 0;
            z2 = *xc;
            do {
                z = (*x & 0xffff) * y + (*xc >> 16) + carry;
                carry = z >> 16;
                Storeinc(xc, z, z2);
                z2 = (*x++ >> 16) * y + (*xc & 0xffff) + carry;
                carry = z2 >> 16;
            } while (x < xae);
            *xc = z2;
        }
    }
    for (xc0 = c->x, xc = xc0 + wc; wc > 0 && !*--xc; --wc);
    c->wds = wc;
    return c;
}
