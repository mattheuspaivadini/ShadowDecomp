/* asm/cod/014DE8.s -> sceDmaRecvN.
 * SCE libvifpk/libdma (cc=29)
 * MATCHED. */
typedef struct {
    unsigned int DIR:1;
    unsigned int p0:1;
    unsigned int MOD:2;
    unsigned int ASP:2;
    unsigned int TTE:1;
    unsigned int TIE:1;
    unsigned int STR:1;
    unsigned int p1:7;
    unsigned int TAG:16;
} tD_CHCR;

typedef struct sceDmaChan {
    tD_CHCR chcr;
    int p0[3];
    volatile int madr;
    int p1[3];
    int qwc;
    int p2[3];
    int tadr;
} sceDmaChan;

unsigned int func_001148B8(unsigned int x);
void func_001147C0(sceDmaChan *p);

void sceDmaRecvN(sceDmaChan *p, unsigned int x, int qwc) {
    int r = func_001148B8(x);
    func_001147C0(p);
    if ((unsigned int)p->madr != 0xFFFFFFFFU)
        p->madr = r;
    p->qwc = qwc;
    p->chcr.MOD = 0;
    p->chcr.DIR = 0;
    p->chcr.STR = 1;
}
