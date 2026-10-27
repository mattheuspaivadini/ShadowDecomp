/* KERNEL.XFF @ 0x034030 (184 B) - sceCdStatus
 * Evidence: prechk(2) else -1; RPC function 0xC with a 4-byte reply; -1 on RPC failure; prints .rodata+0x3710 "status called" when SCE_CD_debug > 1; returns the reply word. libcdvd S-command RPC template (prechk, sceSifCallRpc on _sceCd_cd_scmd with _sceCd_scmdrdata as the receive buffer, read through the uncached alias | 0x20000000, SignalSema(_sceCd_scmd_semid)); SCE library code, built with cc=29 (2.9 frame layout). UNCONFIRMED: client struct kept opaque.
 */
typedef struct {
    char pad[0x28];
} sceSifClientData;
extern sceSifClientData _sceCd_cd_scmd;
extern int _sceCd_scmdrdata[];
extern int _sceCd_scmd_semid;
extern int SCE_CD_debug;
extern char D_kernel_rodata_3710[];
int _sceCd_scmd_prechk(int cmd);
int sceSifCallRpc(sceSifClientData *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *end_para);
int SignalSema(int sema);
int scePrintf(const char *fmt, ...);

int sceCdStatus(void) {
    int result;

    if (_sceCd_scmd_prechk(2) == 0) {
        return -1;
    }
    if (sceSifCallRpc(&_sceCd_cd_scmd, 0xC, 0, 0, 0, _sceCd_scmdrdata, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return -1;
    }
    result = *(int *)((unsigned int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid);
    if (SCE_CD_debug > 1) {
        scePrintf(D_kernel_rodata_3710);
    }
    return result;
}
