/* asm/cod/018288.s -> sceCdMmode.
 * sceCdMmode; send-buffer pointer local (Session 23)
 * MATCHED. */
extern char _sceCd_cd_scmd[];
extern int _sceCd_scmdsdata[];
extern char _sceCd_scmdrdata[];
extern int D_001355E8[];
extern int D_001355EC[];
extern int D_001355F0[];
extern int _sceCd_scmd_semid[];
int sceSifCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *ea);
int _sceCd_scmd_prechk(int a0);
int sceSifWriteBackDCache(void *p, int n);
int SignalSema(int a0);

int sceCdMmode(int media) {
    int *sd = _sceCd_scmdsdata;
    int r;
    if (_sceCd_scmd_prechk(0x22) == 0) return 0;
    sd[0] = media;
    sceSifWriteBackDCache(sd, 4);
    if (sceSifCallRpc(_sceCd_cd_scmd, D_001355E8[0], 0, sd, D_001355EC[0], _sceCd_scmdrdata, D_001355F0[0], 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    r = *(int *)((unsigned int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return r;
}
