/* asm/cod/014CB0.s -> sceDmaSendN.
 * sceDmaSendN (SHN_ABS)
 * MATCHED (Session 12). */
typedef struct sceDmaChan {
    int chcr;
    int p0[3];
    volatile int madr;
    int p1[3];
    int qwc;
    int p2[3];
    int tadr;
} sceDmaChan;

unsigned int func_001148B8(unsigned int x);
void func_001147C0(sceDmaChan *p);

int sceDmaSendN(sceDmaChan *p, unsigned int x, int qwc) {
    int r = func_001148B8(x);
    func_001147C0(p);
    if ((unsigned int)p->madr != 0xFFFFFFFFU)
        p->madr = r;
    p->qwc = qwc;
    return p->chcr = (p->chcr & -13) | 0x101;
}
