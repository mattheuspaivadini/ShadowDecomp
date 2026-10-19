/* asm/cod/012CC8.s -> func_00112CC8.
 * SCE sifcmd send-command core behind sceSifSendCmd/isceSifSendCmd (mode bit0 = isceSifSetDma, bit2 = write back src); int DMA fields keep the store order
 * MATCHED. */
typedef struct {
    unsigned int psize:8;       /* 0x00 packet size */
    unsigned int dsize:24;      /*      extra data size */
    void *dest;                 /* 0x04 */
    int cid;                    /* 0x08 */
    unsigned int opt;           /* 0x0C */
} sceSifCmdHdr;

typedef struct {
    int src;                  /* 0x00 */
    int dest;                 /* 0x04 */
    int size;                   /* 0x08 */
    int attr;                   /* 0x0C */
} sceSifDmaData;

extern int D_0014B360 __attribute__((section(".bss")));   /* IOP-side command buffer */

void sceSifWriteBackDCache(void *ptr, int size);
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
unsigned int isceSifSetDma(sceSifDmaData *sdd, int len);

unsigned int func_00112CC8(int cid, int mode, sceSifCmdHdr *pkt, int pktsize,
                           void *src, void *dest, int size) {
    sceSifDmaData dmat[2];
    int n;

    if (pktsize < 0x10 || pktsize > 0x70)
        return 0;
    n = 0;
    if (size > 0) {
        n = 1;
        pkt->dsize = size;
        dmat[0].src = (int)src;
        dmat[0].dest = (int)dest;
        pkt->dest = dest;
        dmat[0].size = size;
        dmat[0].attr = 0;
        if (mode & 4)
            sceSifWriteBackDCache(src, size);
    } else {
        pkt->dsize = 0;
        pkt->dest = 0;
    }
    dmat[n].src = (int)pkt;
    dmat[n].dest = D_0014B360;
    dmat[n].size = pktsize;
    pkt->cid = cid;
    pkt->psize = pktsize;
    dmat[n].attr = 0x44;
    sceSifWriteBackDCache(pkt, pktsize);
    n++;
    if (mode & 1)
        return isceSifSetDma(dmat, n);
    return sceSifSetDma(dmat, n);
}
