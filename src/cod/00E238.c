/* asm/cod/00E238.s -> func_0010E238.
 * SIF RPC client init: bind/poll loop nested under the not-yet-bound check, 4-byte char struct copy (Session 22)
 * MATCHED. */
struct SifRpcClientData {
    char pad00[0x24];
    void *server;       /* 0x24 */
    char pad28[0x28 - 0x28];
};
struct B4 { unsigned char b[4]; };
extern int D_00132330 __attribute__((section(".data")));
extern struct SifRpcClientData D_00147580;
extern struct B4 D_00147380 __attribute__((section(".bss")));
extern struct B4 D_001475A8 __attribute__((section(".bss")));

int sceSifBindRpc(struct SifRpcClientData *cd, int rpc, int mode);
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *arg);

int func_0010E238(void) {
    int i;

    if (D_00132330 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00147580, 0x80000006, 0) < 0)
                return -1;
            if (D_00147580.server != 0) {
                D_00132330 = 0;
                if (sceSifCallRpc(&D_00147580, 0xFF, 0, 0, 0, &D_00147380, 4, 0, 0) < 0)
                    return 0xFFFEFFFF;
                D_001475A8 = D_00147380;
                return 0;
            }
            for (i = 0x100000; --i != -1; )
                ;
        }
    }
    return 0;
}
