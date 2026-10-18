/* asm/cod/0169D8.s -> sceDbcSendData3.
 * sceDbcSendData3; DbcPkt struct filled through a local pointer, byte copy loop (Session 22)
 * MATCHED. */
struct SifRpcClientData { char pad[0x28]; };
struct DbcPkt {
    int port;           /* 0x00 */
    int slot;           /* 0x04 */
    int size;           /* 0x08 */
    unsigned char data[0x2084];   /* 0x0C */
};
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *arg);
int WaitSema(int sema);
int SignalSema(int sema);
int sceSifCheckStatRpc(struct SifRpcClientData *cd);
void func_00116C58(const char *fmt, ...);

extern int D_00150DC0 __attribute__((section(".bss")));
extern struct SifRpcClientData D_0014E950;
extern struct DbcPkt D_0014EAC0;
extern char D_001387F8[];
extern char D_00138828[];

int sceDbcSendData3(int port, int slot, int *size, unsigned char *data, void *end) {
    int i;

    if (*size >= 0x2081) {
        func_00116C58(D_001387F8, *size);
        return 0;
    }
    WaitSema(D_00150DC0);
    if (sceSifCheckStatRpc(&D_0014E950) == 1) {
        func_00116C58(D_00138828);
        SignalSema(D_00150DC0);
        return 0;
    }
    {
        struct DbcPkt *p = &D_0014EAC0;
        p->port = port;
        p->slot = slot;
        p->size = *size;
        for (i = 0; i < *size; i++)
            p->data[i] = data[i];
    }
    if (sceSifCallRpc(&D_0014E950, 0x8000131C, 1, &D_0014EAC0, 0x2090,
                      &D_0014EAC0, 0x2090, end, 0) < 0) {
        SignalSema(D_00150DC0);
        return 0;
    }
    SignalSema(D_00150DC0);
    return 1;
}
