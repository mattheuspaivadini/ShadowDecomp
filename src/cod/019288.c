/* asm/cod/019288.s -> sceLibnetInitialize.
 * sceLibnetInitialize; 64-byte-aligned size check + the SIF bind/retry/delay loop (Session 23)
 * MATCHED. */
struct SifRpcClientData { char pad00[0x24]; void *server; };   /* ps2sdk SifRpcClientData: server at 0x24 */
int sceSifMBindRpcParam(struct SifRpcClientData *cd, int rpc, int mode, int size, int a4, int a5);

int sceLibnetInitialize(struct SifRpcClientData *cd, int size, int a2, int a3) {
    int i;

    if (size < 0x100 || size != ((size + 63) & ~63))
        return -0x21F;
    while (1) {
        if (sceSifMBindRpcParam(cd, 0x80001201, 0, size, a2, a3) < 0)
            return -0x21C;
        if (cd->server != 0)
            break;
        for (i = 0x10000; --i != -1; )
            ;
    }
    return 0;
}
