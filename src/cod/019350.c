/* asm/cod/019350.s -> sceLibnetTerminate.
 * sceLibnetTerminate; unbind/retry loop with the empty 0x10000 delay loop, mirror of sceLibnetInitialize (019288) (Session 28).
 * MATCHED. */
struct SifRpcClientData { char pad00[0x24]; void *server; };   /* ps2sdk SifRpcClientData: server at 0x24 */
int sceSifMUnBindRpc(struct SifRpcClientData *cd, int mode);

int sceLibnetTerminate(struct SifRpcClientData *cd) {
    int r;
    int i;

    while (1) {
        r = sceSifMUnBindRpc(cd, 0);
        if (r < 0)
            return -0x21C;
        if (r == 1)
            break;
        for (i = 0x10000; --i != -1; )
            ;
    }
    return 0;
}
