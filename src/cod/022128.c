/* asm/cod/022128.s -> sceNetcnfifSetup.
 * sceNetcnfifSetup; bind/retry loop like sceSifInitIopHeap (Session 23)
 * MATCHED. */
struct SifRpcClientData { char pad00[0x24]; void *server; };   /* ps2sdk SifRpcClientData: server at 0x24 */
extern int D_0013595C[];
extern struct SifRpcClientData D_00167EC0;
int sceSifBindRpc(struct SifRpcClientData *cd, int rpc, int mode);
int sceSifCheckStatRpc(struct SifRpcClientData *cd);

int sceNetcnfifSetup(void) {
    int i;
    if (D_0013595C[0] != 0) return 0;
    while (1) {
        if (sceSifBindRpc(&D_00167EC0, 0x80001101, 1) < 0) return -1;
        while (sceSifCheckStatRpc(&D_00167EC0) != 0)
            ;
        if (D_00167EC0.server != 0) break;
        for (i = 0x10000; --i != -1; )
            ;
    }
    D_0013595C[0] = 1;
    return 0;
}
