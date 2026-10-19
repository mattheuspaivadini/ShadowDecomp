/* asm/cod/00EF98.s -> sceSifResetIop.
 * SCE sif IOP reset packet (cid 0x80000003); 16-aligned packet makes the dsize bitfield a 64-bit ld/and/sd
 * MATCHED. */
typedef struct {
    unsigned int psize:8;       /* 0x00 packet size */
    unsigned int dsize:24;      /*      extra data size */
    int dest;                   /* 0x04 */
    int cid;                    /* 0x08 */
    unsigned int opt;           /* 0x0C */
} sceSifCmdHdr;

struct SifResetPkt {
    sceSifCmdHdr hdr;           /* 0x00 */
    int  arglen;                /* 0x10 */
    int  mode;                  /* 0x14 */
    char arg[0x50];             /* 0x18 */
} __attribute__((aligned(16)));

typedef struct {
    int src;                    /* 0x00 */
    int dest;                   /* 0x04 */
    int size;                   /* 0x08 */
    int attr;                   /* 0x0C */
} sceSifDmaData;

extern struct SifResetPkt D_001475C0;

int sceSifExecNotifyHandler(int a0, int a1);
void sceSifStopDma(void);
int sceSifGetReg(int id);
void sceSifSetReg(int id, int val);
void sceSifWriteBackDCache(void *ptr, int size);
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);

int sceSifResetIop(const char *arg, int mode) {
    sceSifDmaData dma;
    int i;
    int iop;

    sceSifExecNotifyHandler(0, 0);
    sceSifExecNotifyHandler(1, 0);
    sceSifStopDma();
    iop = sceSifGetReg(0x80000000);
    D_001475C0.mode = mode;
    for (i = 0; arg[i] != 0; i++)
        D_001475C0.arg[i] = arg[i];
    D_001475C0.hdr.dest = 0;
    D_001475C0.arglen = i;
    D_001475C0.hdr.cid = 0x80000003;
    D_001475C0.hdr.dsize = 0;
    D_001475C0.hdr.psize = 0x68;
    dma.dest = iop;
    dma.size = 0x68;
    dma.attr = 0x44;
    dma.src = (int)&D_001475C0;
    sceSifWriteBackDCache(&D_001475C0, 0x68);
    sceSifSetReg(4, 0x40000);
    if (sceSifSetDma(&dma, 1) != 0) {
        sceSifSetReg(4, 0x10000);
        sceSifSetReg(4, 0x20000);
        sceSifSetReg(0x80000002, 0);
        sceSifSetReg(0x80000000, 0);
        return 1;
    }
    return 0;
}
