/* asm/cod/016EF8.s -> _sceCd_cd_read_intr.
 * _sceCd_cd_read_intr; typed reply record copied through the uncached alias, the uncached destination computed first (Session 23)
 * MATCHED. */
struct RD { int n0; int n1; unsigned char *dst0; unsigned char *dst1; unsigned char d0[0x40]; unsigned char d1[0x40]; };
extern int sceCdCbfunc_num[];
void _sceCd_cd_callback(int *a0);
#define UNCACHED(p) ((unsigned char *)((unsigned int)(p) | 0x20000000))

void _sceCd_cd_read_intr(struct RD *rd) {
    struct RD *p;
    int i;
    unsigned char *d, *u;
    p = (struct RD *)UNCACHED(rd);
    if (p->n0 > 0) {
        u = UNCACHED(p->dst0); d = p->dst0;
        for (i = 0; i < p->n0; i++) {
            unsigned char c = p->d0[i];
            u[i] = c;
            d[i] = c;
        }
    }
    if (p->n1 > 0) {
        u = UNCACHED(p->dst1); d = p->dst1;
        for (i = 0; i < p->n1; i++) {
            unsigned char c = p->d1[i];
            u[i] = c;
            d[i] = c;
        }
    }
    _sceCd_cd_callback(sceCdCbfunc_num);
}
