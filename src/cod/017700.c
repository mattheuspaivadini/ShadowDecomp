/* asm/cod/017700.s -> SceSifrpcCall.
 * 9-arg cmd 0xE + uncached mirror read; famA (R3)
 * MATCHED (Session 8). */
extern char _sceCd_cd_ncmd[];   /* request struct -> lui/%lo */
extern char _sceCd_ncmdrdata[];   /* 4-byte reply buffer -> lui/%lo */
extern int _sceCd_ncmd_semid[];    /* handle word -> lui/%lo */

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int _sceCd_ncmd_prechk(int a0);
int SignalSema(int a0);

int sceCdNcmdDiskReady(void) {
    int r;

    if (_sceCd_ncmd_prechk(2) == 0)
        return 0;
    r = sceSifCallRpc((int)_sceCd_cd_ncmd, 0xE, 0, 0, 0, (int)_sceCd_ncmdrdata, 4, 0, 0);
    if (r < 0) {
        SignalSema(_sceCd_ncmd_semid[0]);
        return 0;
    }
    r = *(int *)((unsigned int)_sceCd_ncmdrdata | 0x20000000);
    SignalSema(_sceCd_ncmd_semid[0]);
    return r;
}
