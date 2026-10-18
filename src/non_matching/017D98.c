/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 45 [cc=29] (was 61).
 * sceCdDiskReady_old: shared fail tail (goto), debug/semaphore globals as non-small arrays, DIntr result tested after the module flag store. Residual = register roles (SCE_CD_debug base lands in s5 instead of s6, 4 s-regs permuted) and the movz/movn polarity of the 8 -> -1 : 6 select.
 * The original .s stays in the build (asm/cod/017D98.s); this C
 * draft (Session 23) is kept for the record. */
struct SifRpcClientData { char pad00[0x24]; void *server; };
extern int SCE_CD_debug[];
extern int _sceCd_old_module[];
extern int _sceCd_scmd_semid[];
extern int D_00133A90[];
extern char D_00138A30[];
extern char D_00138A48[];
extern char D_00138A68[];
extern struct SifRpcClientData D_00151050;
extern int D_00151090[];
extern char _sceCd_scmdrdata[];
int scePrintf(const char *fmt, ...);
int DIntr(void);
int EIntr(void);
void _sceCdInitSema(void);
int PollSema(int s);
int SignalSema(int s);
int sceCdSyncS(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int rpc, int mode);
void sceSifInitRpc(int mode);
int sceSifWriteBackDCache(void *p, int n);
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void *end, void *ea);

int sceCdDiskReady_old(int mode) {
    int i;
    int r;

    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138A30);
    r = DIntr();
    _sceCd_old_module[0] = 1;
    if (r)
        EIntr();
    _sceCdInitSema();
    if (PollSema(_sceCd_scmd_semid[0]) != _sceCd_scmd_semid[0])
        return 6;
    if (sceCdSyncS(1) != 0)
        goto fail;
    sceSifInitRpc(0);
    if (D_00133A90[0] < 0) {
        while (1) {
            if (sceSifBindRpc(&D_00151050, 0x8000059A, 0) < 0) {
                if (SCE_CD_debug[0] > 0)
                    scePrintf(D_00138A48);
                for (i = 0x100000; --i != -1; )
                    ;
                continue;
            }
            if (D_00151050.server != 0)
                break;
            for (i = 0x100000; --i != -1; )
                ;
        }
        D_00133A90[0] = 0;
    }
    D_00151090[0] = mode;
    sceSifWriteBackDCache(D_00151090, 4);
    if (sceSifCallRpc(&D_00151050, 0, 0, D_00151090, 4, _sceCd_scmdrdata, 4, 0, 0) < 0)
        goto fail;
    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138A68);
    r = *(int *)((unsigned int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return r;
fail:
    SignalSema(_sceCd_scmd_semid[0]);
    r = 6;
    if (mode == 8)
        r = -1;
    return r;
}
