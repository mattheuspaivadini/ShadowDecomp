/* asm/cod/00DCE8.s -> sceSifInitIopHeap.
 * sceSifInitIopHeap; bind/retry loop + memory barrier before return (Session 23)
 * MATCHED. */
struct SifRpcClientData {
    char pad00[0x24];
    void *server;       /* 0x24 */
};
extern struct SifRpcClientData D_001471C0;
extern int D_0013232C __attribute__((section(".data")));

int sceSifBindRpc(struct SifRpcClientData *cd, int rpc, int mode);

int sceSifInitIopHeap(void) {
    int i;

    while (1) {
        if (sceSifBindRpc(&D_001471C0, 0x80000003, 0) < 0)
            return -1;
        if (D_001471C0.server != 0)
            break;
        for (i = 0x100000; --i != -1; )
            ;
    }
    D_0013232C = 0;
    __asm__ volatile ("" ::: "memory");   /* keeps the store ahead of the return value (scheduling barrier) */
    return 0;
}
