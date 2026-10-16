/* asm/cod/02E9C8.s -> _s2b.
 * Newlib mprec.c _s2b; authentic source, Bigint offsets confirmed by matched _Balloc
 * MATCHED. */
struct S02E9C8 {
    void         *next;     /* 0x00 */
    int           k;        /* 0x04 */
    int           maxwds;   /* 0x08 */
    int           sign;     /* 0x0C */
    int           wds;      /* 0x10 */
    unsigned int  x[1];     /* 0x14 */
};

extern void *_Balloc(void *p, int i);
extern struct S02E9C8 *_multadd(void *p, struct S02E9C8 *b, int m, int a);

struct S02E9C8 *_s2b(void *p, const char *s, int nd0, int nd, unsigned int y9)
{
    struct S02E9C8 *b;
    int i, k;
    int x, y;

    x = (nd + 8) / 9;
    for (k = 0, y = 1; x > y; y <<= 1, k++) ;
    b = (struct S02E9C8 *)_Balloc(p, k);
    b->x[0] = y9;
    b->wds = 1;

    i = 9;
    if (9 < nd0) {
        s += 9;
        do {
            b = _multadd(p, b, 10, *s++ - '0');
        } while (++i < nd0);
        s++;
    } else
        s += 10;
    for (; i < nd; i++)
        b = _multadd(p, b, 10, *s++ - '0');
    return b;
}
