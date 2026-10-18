/* asm/cod/016568.s -> sceDbcSRData.
 * sceDbcSRData; DbcSRPkt (send/recv halves) through a local pointer (Session 22)
 * MATCHED. */
struct SifRpcClientData { char pad[0x28]; };
struct DbcSRPkt {
    int port;               /* 0x00 */
    int slot;               /* 0x04 */
    int ssize;              /* 0x08 */
    int rsize;              /* 0x0C */
    unsigned char sdata[0x80];  /* 0x10 */
    unsigned char rdata[0x80];  /* 0x90 */
    int result;             /* 0x110 */
};
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *arg);
int WaitSema(int sema);
int SignalSema(int sema);
void func_00116C58(const char *fmt, ...);

extern int D_00150DC0 __attribute__((section(".bss")));
extern struct SifRpcClientData D_0014E900;
extern struct DbcSRPkt D_0014EA00;
extern char D_00138748[];

int sceDbcSRData(int port, int slot, int *ssize, unsigned char *sdata, int *rsize, unsigned char *rdata) {
    struct DbcSRPkt *p;
    int i;
    int r;

    WaitSema(D_00150DC0);
    p = &D_0014EA00;
    p->port = port;
    p->slot = slot;
    p->ssize = *ssize;
    p->rsize = *rsize;
    for (i = 0; i < *ssize; i++)
        p->sdata[i] = sdata[i];
    if (sceSifCallRpc(&D_0014E900, 0x80001318, 0, &D_0014EA00, 0x90,
                      &D_0014EA00, 0x90, 0, 0) < 0) {
        func_00116C58(D_00138748);
        SignalSema(D_00150DC0);
        return 0;
    }
    if (p->result >= 0) {
        *ssize = p->ssize;
        *rsize = p->rsize;
        for (i = 0; i < p->rsize; i++)
            rdata[i] = p->rdata[i];
    }
    r = p->result;
    SignalSema(D_00150DC0);
    return r;
}
