/* asm/cod/00DEF8.s -> sceSifLoadIopHeap.
 * sceSifLoadIopHeap; HeapPkt {addr, path[252]} with break-on-NUL copy loop (Session 22)
 * MATCHED. */
struct SifRpcClientData { char pad[0x28]; };
struct HeapPkt {
    void *addr;         /* 0x00 */
    char path[252];     /* 0x04 */
};
extern int D_0013232C __attribute__((section(".data")));
extern struct HeapPkt D_00147280;
extern struct SifRpcClientData D_001471C0;
extern int D_00147200 __attribute__((section(".bss")));

int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *arg);

int sceSifLoadIopHeap(const char *path, void *addr) {
    int i;

    if (D_0013232C < 0)
        return 0;
    for (i = 0; i < 252; i++) {
        if ((D_00147280.path[i] = path[i]) == 0)
            break;
    }
    if (i == 252) {
        i = 251;
        D_00147280.path[251] = 0;
    }
    D_00147280.addr = addr;
    D_00147280.path[251] = 0;
    if (sceSifCallRpc(&D_001471C0, 3, 0, &D_00147280, i + 5, &D_00147200, 4, 0, 0) < 0)
        return -1;
    return D_00147200;
}
