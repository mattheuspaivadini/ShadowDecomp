/* asm/cod/016828.s -> sceDbcSendData2.
 * sceDbcSendData2; double-buffered DbcPktC0/client-data arrays indexed by the re-read slot counter (Session 22)
 * MATCHED. */
struct SifRpcClientData { char pad[0x28]; };
struct DbcPktC0 {
    int port;               /* 0x00 */
    int slot;               /* 0x04 */
    int size;               /* 0x08 */
    unsigned char data[0x80];   /* 0x0C */
    int result;             /* 0x8C */
    char pad90[0x30];
};
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *arg);
int sceSifCheckStatRpc(struct SifRpcClientData *cd);
int WaitSema(int sema);
int SignalSema(int sema);
void func_00116C58(const char *fmt, ...);

extern int D_00150DC0 __attribute__((section(".bss")));
extern struct DbcPktC0 D_00150B80[2];
extern struct SifRpcClientData D_0014E978[2];
extern int D_00133A2C __attribute__((section(".data")));
extern char D_00138788[];
extern char D_001387B8[];
extern char D_001387D8[];

int sceDbcSendData2(int port, int slot, int *size, unsigned char *data) {
    struct DbcPktC0 *p;
    int i;

    if (*size >= 0x81) {
        func_00116C58(D_00138788, *size);
        return 0;
    }
    WaitSema(D_00150DC0);
    D_00133A2C++;
    if (D_00133A2C >= 2)
        D_00133A2C = 0;
    p = &D_00150B80[D_00133A2C];
    p->port = port;
    p->slot = slot;
    p->size = *size;
    for (i = 0; i < *size; i++)
        p->data[i] = data[i];
    if (sceSifCheckStatRpc(&D_0014E978[D_00133A2C]) == 1) {
        func_00116C58(D_001387B8);
        SignalSema(D_00150DC0);
        return 0;
    }
    if (sceSifCallRpc(&D_0014E978[D_00133A2C], D_00133A2C, 1, &D_00150B80[D_00133A2C], 0x90,
                      &D_00150B80[D_00133A2C], 0x90, 0, 0) < 0) {
        func_00116C58(D_001387D8);
        SignalSema(D_00150DC0);
        return 0;
    }
    SignalSema(D_00150DC0);
    return 1;
}
