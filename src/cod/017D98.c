/* asm/cod/017D98.s -> sceCdDiskReady_old.
 * SCE libcdvd sceCdDiskReady_old (twin of 017FB0 over the S-command semaphore): old-module flag under DIntr, sceCdSyncS gate, bind retry with continue (Session 41)
 * MATCHED. */
struct SifRpcClientData {       /* 0x28 bytes */
    int  pad00[9];
    int  server;                /* 0x24 */
};

extern __attribute__((section(".data"))) int SCE_CD_debug;
extern __attribute__((section(".data"))) volatile int _sceCd_scmd_semid;
extern __attribute__((section(".data"))) int _sceCd_old_module;
extern __attribute__((section(".data"))) int D_00133A90;     /* < 0 until the RPC server is bound */
extern struct SifRpcClientData D_00151050;
extern int D_00151090 __attribute__((section(".bss")));
extern int _sceCd_scmdrdata[];
extern char D_00138A30[];
extern char D_00138A48[];
extern char D_00138A68[];

void scePrintf(const char *fmt, ...);
void _sceCdInitSema(void);
int PollSema(int sema);
int SignalSema(int sema);
int sceCdSyncS(int mode);
void sceSifInitRpc(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int request, int mode);
int DIntr(void);
int EIntr(void);
void sceSifWriteBackDCache(void *addr, int size);
int sceSifCallRpc(struct SifRpcClientData *cd, int rpc, int mode, void *send, int ssize, void *recv,
                  int rsize, void *end, void *param);

int sceCdDiskReady_old(int mode) {
    int i;
    int r;

    if (SCE_CD_debug > 0)
        scePrintf(D_00138A30);
    r = DIntr();
    _sceCd_old_module = 1;
    if (r != 0)
        EIntr();
    _sceCdInitSema();
    if (_sceCd_scmd_semid != PollSema(_sceCd_scmd_semid))
        return 6;
    if (sceCdSyncS(1) != 0) {
        SignalSema(_sceCd_scmd_semid);
        return mode != 8 ? 6 : -1;
    }
    sceSifInitRpc(0);
    if (D_00133A90 < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00151050, 0x8000059A, 0) < 0) {
                if (SCE_CD_debug > 0)
                    scePrintf(D_00138A48);
                i = 0x100000;
                while (i--)
                    ;
                continue;
            }
            if (D_00151050.server != 0) {
                D_00133A90 = 0;
                break;
            }
            i = 0x100000;
            while (i--)
                ;
        }
    }
    D_00151090 = mode;
    sceSifWriteBackDCache(&D_00151090, 4);
    if (sceSifCallRpc(&D_00151050, 0, 0, &D_00151090, 4, _sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return mode != 8 ? 6 : -1;
    }
    if (SCE_CD_debug > 0)
        scePrintf(D_00138A68);
    r = *(int *)((unsigned int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid);
    return r;
}
