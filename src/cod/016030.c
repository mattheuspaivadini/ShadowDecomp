/* asm/cod/016030.s -> sceDbcGetDepNumber.
 * sceDbcGetDepNumber; DbcStat snapshot struct copy under DI/EI, then the RPC (Session 22)
 * MATCHED. */
struct SifRpcClientData { char pad[0x28]; };
struct DbcPkt90 {
    int port;               /* 0x00 */
    int slot;               /* 0x04 */
    int size;               /* 0x08 */
    unsigned char data[0x80];   /* 0x0C */
    int result;             /* 0x8C */
};
struct DbcStat { int w[16]; };
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *arg);
void SyncDCache(void *start, void *end);
int DIntr(void);
int EIntr(void);
int WaitSema(int sema);
int SignalSema(int sema);
void func_00116C58(const char *fmt, ...);

extern struct DbcStat D_00150D00;
extern struct DbcStat D_00150D80;
extern int D_00150DC0 __attribute__((section(".bss")));
extern struct SifRpcClientData D_0014E900;
extern struct DbcPkt90 D_0014EA00;
extern char D_001386C0[];

int sceDbcGetDepNumber(int port) {
    struct DbcPkt90 *p;
    int r;

    SyncDCache(&D_00150D00, (char *)&D_00150D00 + 0x80);
    DIntr();
    D_00150D80 = D_00150D00;
    EIntr();
    if (D_00150D80.w[port] != 1)
        return -12;
    WaitSema(D_00150DC0);
    D_0014EA00.port = port;
    if (sceSifCallRpc(&D_0014E900, 0x80001303, 0, &D_0014EA00, 0x90,
                      &D_0014EA00, 0x90, 0, 0) < 0) {
        func_00116C58(D_001386C0);
        SignalSema(D_00150DC0);
        return 0;
    }
    r = D_0014EA00.slot;
    SignalSema(D_00150DC0);
    return r;
}
