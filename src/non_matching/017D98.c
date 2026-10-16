/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 53 [cc=29].
 * R3 famD: busy-wait + retry loop (4 in-body nops)
 * The original .s stays in the build (asm/cod/017D98.s); this C
 * draft (Session 8) is kept for the record. */
int scePrintf(const char *msg);
int DIntr(void);
void EIntr(void);
void _sceCdInitSema(void);
int PollSema(int a0);
void SignalSema(int a0);
int sceCdSyncS(int a0);
int sceSifBindRpc(int a0, int a1, int a2);
void sceSifInitRpc(int a0);
int sceSifWriteBackDCache(int a0, int a1);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern int SCE_CD_debug[];    /* lui/%lo (non-small) */
extern int _sceCd_old_module[];    /* lui/%lo */
extern int _sceCd_scmd_semid[];    /* lui/%lo */
extern int D_00133A90[];    /* lui/%lo */
extern char D_00138A30[];   /* lui/addiu */
extern char D_00138A48[];   /* lui/addiu */
extern char D_00138A68[];   /* lui/addiu */
extern char D_00151050[];   /* lui/addiu, command object */
extern char D_00151090[];   /* lui/addiu, request block */
extern char _sceCd_scmdrdata[];   /* lui/addiu, reply block   */

int sceCdDiskReady_old(int a0) {
    int i;
    int r;

    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138A30);
    r = DIntr();
    _sceCd_old_module[0] = 1;
    if (r != 0)
        EIntr();
    _sceCdInitSema();
    if (_sceCd_scmd_semid[0] != PollSema(_sceCd_scmd_semid[0]))
        return 6;
    if (sceCdSyncS(1) != 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return (a0 == 8) ? -1 : 6;
    }
    sceSifInitRpc(0);
    if (D_00133A90[0] < 0) {
        for (;;) {
            if (sceSifBindRpc((int)D_00151050, 0x8000059A, 0) < 0) {
                if (SCE_CD_debug[0] > 0)
                    scePrintf(D_00138A48);
                i = 0x100000;
                while (i != -1) {
                    i--;
                    __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
                }
                continue;
            }
            if (D_00151050[9] != 0)
                break;
            i = 0x100000;
            while (i != -1) {
                i--;
                __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
            }
        }
        D_00133A90[0] = 0;
    }
    D_00151090[0] = a0;
    sceSifWriteBackDCache((int)D_00151090, 4);
    if (sceSifCallRpc((int)D_00151050, 0, 0, (int)D_00151090, 4,
                      (int)_sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return (a0 == 8) ? -1 : 6;
    }
    if (SCE_CD_debug[0] > 0)
        scePrintf(D_00138A68);
    r = *(int *)(((int)_sceCd_scmdrdata) | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return r;
}
