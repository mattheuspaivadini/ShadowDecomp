/* asm/cod/0181D0.s -> SceSifrpcCall.
 * func_001178A8 guard + double mirror read; famA (R3)
 * MATCHED (Session 8). */
extern char _sceCd_cd_scmd[];   /* request struct -> lui/%lo */
extern char _sceCd_scmdrdata[];   /* 8-byte reply buffer -> lui/%lo */
extern int _sceCd_scmd_semid[];    /* handle word -> lui/%lo */

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int _sceCd_scmd_prechk(int a0);
int SignalSema(int a0);

int sceCdPowerOff(int *a0) {
    int r;

    if (_sceCd_scmd_prechk(0x21) == 0)
        return 0;
    r = sceSifCallRpc((int)_sceCd_cd_scmd, 0x21, 0, 0, 0, (int)_sceCd_scmdrdata, 8, 0, 0);
    if (r < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    *a0 = *(int *)((unsigned int)((int)_sceCd_scmdrdata + 4) | 0x20000000);
    r = *(int *)((unsigned int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return r;
}
