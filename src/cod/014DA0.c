/* asm/cod/014DA0.s -> sceDmaRecv.
 * sceDmaRecv (SHN_ABS)
 * MATCHED (Session 12). */
typedef struct sceDmaChan {
    int chcr;
    int p0[3];
    int madr;
    int p1[3];
    int qwc;
    int p2[3];
    int tadr;
} sceDmaChan;

void func_001147C0(sceDmaChan *p);

int sceDmaRecv(sceDmaChan *p) {
    func_001147C0(p);
    p->qwc = 0;
    return p->chcr = ((((p->chcr & -13) | 4) & -2) | 0x100);
}
