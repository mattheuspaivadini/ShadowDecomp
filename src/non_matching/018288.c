/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 27 [cc=29].
 * R3 famB: func_001178A8 gate + mirror read
 * The original .s stays in the build (asm/cod/018288.s); this C
 * draft (Session 8) is kept for the record. */
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int _sceCd_scmd_prechk(int a0);
int sceSifWriteBackDCache(int a0, int a1);
int SignalSema(int a0);

extern int _sceCd_scmdsdata[];    /* .data 0x00135080, 0x540 bytes, lui/%lo */
extern int _sceCd_scmdrdata[];    /* .data 0x00134C40, 0x440 bytes, lui/%lo */
extern int _sceCd_cd_scmd[];    /* .data 0x001355C0, 0x28 bytes, lui/%lo */
extern int D_001355E8[];    /* .data 0x001355E8 = 0x22, lui/%lo */
extern int D_001355EC[];    /* .data 0x001355EC = 4, lui/%lo */
extern int D_001355F0[];    /* .data 0x001355F0 = 4, lui/%lo */
extern int _sceCd_scmd_semid[];    /* .data 0x00133A6C, lui/%lo */

int sceCdMmode(int a0) {
    unsigned int addr;

    if (_sceCd_scmd_prechk(0x22) == 0)
        return 0;
    _sceCd_scmdsdata[0] = a0;
    sceSifWriteBackDCache((int)_sceCd_scmdsdata, 4);
    if (sceSifCallRpc((int)_sceCd_cd_scmd, D_001355E8[0], 0, (int)_sceCd_scmdsdata,
                      D_001355EC[0], (int)_sceCd_scmdrdata, D_001355F0[0], 0,
                      0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    addr = (unsigned int)_sceCd_scmdrdata | 0x20000000;
    SignalSema(_sceCd_scmd_semid[0]);
    return *(int *)addr;
}
