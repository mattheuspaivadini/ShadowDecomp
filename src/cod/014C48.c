/* asm/cod/014C48.s -> sceDmaSend.
 * sceDmaSend (SHN_ABS)
 * MATCHED (Session 12). */
typedef struct sceDmaChan {
    int chcr;
    int p0[3];
    int madr;
    int p1[3];
    int qwc;
    int p2[3];
    volatile int tadr;
} sceDmaChan;

unsigned int func_001148B8(unsigned int x);
void func_001147C0(sceDmaChan *p);

int sceDmaSend(sceDmaChan *p, unsigned int x) {
    int r = func_001148B8(x);
    func_001147C0(p);
    if ((unsigned int)p->tadr != 0xFFFFFFFFU)
        p->tadr = r;
    p->qwc = 0;
    return p->chcr = (p->chcr & -13) | 0x105;
}
