/* asm/cod/017838.s -> func_00109B80.
 * drain loop + post-body guard; wave3d (R1)
 * MATCHED (Session 8). */
int sceSifCheckStatRpc(int *a);
int scePrintf(const char *msg);
void DelayThread(int a0);

extern int SCE_CD_debug[];    /* lui/%lo (non-small) */
extern char D_001389B0[];   /* lui/%lo */
extern char _sceCd_cd_scmd[];   /* lui/%lo, passed as the func_00109B80 argument */

int sceCdSyncS(int a0) {
    if (a0 == 0) {
        if (SCE_CD_debug[0] > 0)
            scePrintf(D_001389B0);
        while (sceSifCheckStatRpc((int *)_sceCd_cd_scmd) != 0)
            DelayThread(0xFA0);
        return 0;
    }
    return sceSifCheckStatRpc((int *)_sceCd_cd_scmd);
}
