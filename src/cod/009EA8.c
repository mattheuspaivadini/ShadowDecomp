/* asm/cod/009EA8.s -> sceSifExecRequest.
 * sceSifExecRequest (sifrpc sif_exec_request); typed server-data/rend packets, uniform sceSifDmaData fields, retry loop re-testing the SetDma result (Session 23)
 * MATCHED. */
typedef void *(*SifRpcFunc)(int fno, void *buf, int size);
typedef struct {
    int sid;                /* 0x00 */
    SifRpcFunc func;        /* 0x04 */
    void *buf;              /* 0x08 */
    int size;               /* 0x0C */
    SifRpcFunc cfunc;       /* 0x10 */
    void *cbuf;             /* 0x14 */
    int csize;              /* 0x18 */
    void *client;           /* 0x1C */
    void *pkt_addr;         /* 0x20 */
    int rpc_number;         /* 0x24 */
    void *receive;          /* 0x28 */
    int rsize;              /* 0x2C */
    int rmode;              /* 0x30 */
    unsigned int rid;       /* 0x34 */
} SifRpcServerData;
typedef struct {
    char hdr[0x10];
    int rec_id;             /* 0x10 */
    void *pkt_addr;         /* 0x14 */
    int rpc_id;             /* 0x18 */
    void *client;           /* 0x1C */
    unsigned int cid;       /* 0x20 */
} SifRpcRendPkt;
typedef struct { unsigned int src; unsigned int dest; unsigned int size; unsigned int attr; } SifDmaTransfer;   /* sceSifDmaData: all four fields share one type */
extern char D_00145940[];
int sceSifWriteBackDCache(void *p, int n);
int DIntr(void);
int EIntr(void);
SifRpcRendPkt *func_001092B8(void *rd, unsigned int rid);
SifRpcRendPkt *func_00109288(void *rd);
int sceSifSendCmd(unsigned int cid, void *pkt, int size, void *src, void *dst, int n);
unsigned int sceSifSetDma(SifDmaTransfer *t, int n);

void sceSifExecRequest(SifRpcServerData *sd) {
    SifDmaTransfer dmat[2];
    SifRpcRendPkt *rend;
    void *rec;
    int size = 0;
    int i;
    int j;
    unsigned int r;

    rec = sd->func(sd->rpc_number, sd->buf, sd->size);
    if (rec)
        size = sd->rsize;
    if (sd->size > 0)
        sceSifWriteBackDCache(sd->buf, sd->size);
    if (size > 0)
        sceSifWriteBackDCache(rec, size);
    DIntr();
    if (sd->rid & 4)
        rend = func_001092B8(D_00145940, sd->rid >> 16);
    else
        rend = func_00109288(D_00145940);
    EIntr();
    rend->cid = 0x8000000A;
    rend->client = sd->client;
    if (sd->rmode) {
        while (!sceSifSendCmd(0x80000008, rend, 0x40, rec, sd->receive, size))
            ;
        return;
    }
    rend->rpc_id = 0;
    rend->rec_id = 0;
    i = 0;
    if (size > 0) {
        dmat[0].src = (unsigned int)rec;
        dmat[0].dest = (unsigned int)sd->receive;
        dmat[0].size = (unsigned int)size;
        dmat[0].attr = (unsigned int)0;
        i = 1;
    }
    dmat[i].src = (unsigned int)rend;
    dmat[i].dest = (unsigned int)sd->pkt_addr;
    dmat[i].size = (unsigned int)0x40;
    dmat[i].attr = (unsigned int)0;
    i++;
    do {
        r = sceSifSetDma(dmat, i);
        if (r == 0)
            for (j = 0x100000; --j != -1; )
                ;
    } while (r == 0);
}
