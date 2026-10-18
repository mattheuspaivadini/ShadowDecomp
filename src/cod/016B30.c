/* asm/cod/016B30.s -> sceDbcReceiveData.
 * sceDbcReceiveData; DbcPkt90 through a local pointer, copy-out loop on success (Session 22)
 * MATCHED. */
struct SifRpcClientData { char pad[0x28]; };
struct DbcPkt90 {
    int port;               /* 0x00 */
    int slot;               /* 0x04 */
    int size;               /* 0x08 */
    unsigned char data[0x80];   /* 0x0C */
    int result;             /* 0x8C */
};
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *arg);
int WaitSema(int sema);
int SignalSema(int sema);
void func_00116C58(const char *fmt, ...);

extern int D_00150DC0 __attribute__((section(".bss")));
extern struct SifRpcClientData D_0014E900;
extern struct DbcPkt90 D_0014EA00;
extern char D_00138848[];

int sceDbcReceiveData(int port, int slot, int *size, unsigned char *data) {
    struct DbcPkt90 *p;
    int i;
    int r;

    WaitSema(D_00150DC0);
    p = &D_0014EA00;
    p->port = port;
    p->slot = slot;
    p->size = *size;
    if (sceSifCallRpc(&D_0014E900, 0x8000131A, 0, &D_0014EA00, 0x90,
                      &D_0014EA00, 0x90, 0, 0) < 0) {
        func_00116C58(D_00138848);
        SignalSema(D_00150DC0);
        return 0;
    }
    if (p->result >= 0) {
        *size = p->size;
        for (i = 0; i < p->size; i++)
            data[i] = p->data[i];
    }
    r = p->result;
    SignalSema(D_00150DC0);
    return r;
}
