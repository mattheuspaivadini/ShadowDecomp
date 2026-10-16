/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 129 [cc=29].
 * R3 famD: mode select + movn if-conversion
 * The original .s stays in the build (asm/cod/017AB0.s); this C
 * draft (Session 8) is kept for the record. */
int sceCdSyncS(int a0);
void sceSifInitRpc(int a0);
int sceSifBindRpc(int a0, int a1, int a2);
int scePrintf(const char *msg);
int sceSifWriteBackDCache(int a0, int a1);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void _sceCdInitSema(void);
void func_00117210(void);
void func_00117098(void);

extern int SCE_CD_debug[];    /* lui/%lo (non-small) */
extern int D_00133A64[];    /* lui/%lo */
extern int D_00133A88[];    /* lui/%lo */
extern int D_00133A8C[];    /* lui/%lo */
extern int D_00133A7C[];    /* lui/%lo */
extern int D_00133A94[];    /* lui/%lo */
extern int D_00133A90[];    /* lui/%lo */
extern int _sceCd_ee_read_mode[];    /* lui/%lo */
extern int D_00133A9C[];    /* lui/%lo */
extern int D_00133A98[];    /* lui/%lo */
extern int _sceCd_ncmd_semid[];    /* lui/%lo */
extern int _sceCd_scmd_semid[];    /* lui/%lo */
extern int D_00133A60[];    /* lui/%lo */
extern int _sceCd_CdInit_ON[];    /* lui/%lo */
extern char D_00138A00[];   /* lui/addiu */
extern char D_00138A20[];   /* lui/addiu */
extern char D_00151028[];   /* lui/addiu, command object */
extern char D_00151080[];   /* lui/addiu, request block */
extern char _sceCd_scmdrdata[];   /* lui/addiu, reply block   */

int sceCdInit(int a0) {
    int i;
    int s0;
    int mode;
    int w4;
    int w8;

    if (sceCdSyncS(1) != 0)
        return 0;
    sceSifInitRpc(0);
    D_00133A64[0] = 1;
    D_00133A88[0] = -1;
    D_00133A8C[0] = -1;
    D_00133A7C[0] = -1;
    D_00133A94[0] = -1;
    D_00133A90[0] = -1;
    _sceCd_ee_read_mode[0] = 0;
    D_00133A9C[0] = D_00133A9C[0] + 1;
    D_00133A98[0] = -1;
    for (;;) {
        if (sceSifBindRpc((int)D_00151028, 0x80000592, 0) < 0) {
            if (SCE_CD_debug[0] > 0)
                scePrintf(D_00138A00);
            i = 0x100000;
            while (i != -1) {
                i--;
                __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
            }
            continue;
        }
        if (D_00151028[9] != 0)
            break;
        i = 0x100000;
        while (i != -1) {
            i--;
            __asm__ __volatile__ ("nop\n\tnop\n\tnop\n\tnop");
        }
    }
    D_00151080[0] = a0;
    D_00133A98[0] = 0;
    sceSifWriteBackDCache((int)D_00151080, 4);
    if (sceSifCallRpc((int)D_00151028, 0, 0, (int)D_00151080, 4,
                      (int)_sceCd_scmdrdata, 0x10, 0, 0) < 0) {
        D_00133A64[0] = 0;
        return 0;
    }
    mode = *(int *)((((int)_sceCd_scmdrdata) + 0xC) | 0x20000000);
    w4 = *(int *)((((int)_sceCd_scmdrdata) + 4) | 0x20000000);
    w8 = *(int *)((((int)_sceCd_scmdrdata) + 8) | 0x20000000);
    s0 = 1;
    if (mode == 0xFF) {
        ;
    } else if (mode == 0xFE) {
        SCE_CD_debug[0] = 1;
    } else {
        mode = -1;
        if (((mode < w4 ? w4 : w4 + 0xFF) >> 8) < 2)
            s0 = 2;
        else if (((mode < w8 ? w8 : w8 + 0xFF) >> 8) < 2)
            s0 = 2;
    }
    D_00133A64[0] = 0;
    if (a0 == 5) {
        if (SCE_CD_debug[0] > 0)
            scePrintf(D_00138A20);
        func_00117098();
        _sceCd_ncmd_semid[0] = -1;
        _sceCd_scmd_semid[0] = -1;
        D_00133A60[0] = -1;
        _sceCd_CdInit_ON[0] = 0;
    } else {
        _sceCdInitSema();
        func_00117210();
        _sceCd_CdInit_ON[0] = 1;
    }
    return s0;
}
