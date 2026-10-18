/* STATUS (Session 22, 2026-10-17): NON_MATCHING. best score 3 [cc=29].
 * rotated bind/poll loop; residual = order of the init-flag store vs the return 0 (lui v0/v1)
 * The original .s stays in the build (asm/cod/00DCE8.s); this C
 * draft (Session 22) is kept for the record. */
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
    return D_0013232C = 0;
}
