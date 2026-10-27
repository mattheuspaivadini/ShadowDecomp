/* KERNEL.XFF @ 0x0340E8 (188 B) - sceCdReadClock
 * Evidence: prechk(0xF) else 0; RPC function 1 with a 16-byte reply; 0 on RPC failure; copies the 8-byte clock at reply+4 to rtc (ldl/ldr/sdl/sdr struct copy) and returns the reply word. libcdvd S-command RPC template (prechk, sceSifCallRpc on _sceCd_cd_scmd with _sceCd_scmdrdata as the receive buffer, read through the uncached alias | 0x20000000, SignalSema(_sceCd_scmd_semid)); SCE library code, built with cc=29 (2.9 frame layout). UNCONFIRMED: client struct kept opaque.
 */
typedef struct {
    char pad[0x28];
} sceSifClientData;
typedef struct {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
} sceCdCLOCK;
extern sceSifClientData _sceCd_cd_scmd;
extern int _sceCd_scmdrdata[];
extern int _sceCd_scmd_semid;
extern int SCE_CD_debug;
extern char D_kernel_rodata_3710[];
int _sceCd_scmd_prechk(int cmd);
int sceSifCallRpc(sceSifClientData *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void (*end)(void *), void *end_para);
int SignalSema(int sema);
int scePrintf(const char *fmt, ...);

int sceCdReadClock(sceCdCLOCK *rtc) {
    int result;

    if (_sceCd_scmd_prechk(0xF) == 0) {
        return 0;
    }
    if (sceSifCallRpc(&_sceCd_cd_scmd, 1, 0, 0, 0, _sceCd_scmdrdata, 0x10, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid);
        return 0;
    }
    *rtc = *(sceCdCLOCK *)((unsigned int)&_sceCd_scmdrdata[1] | 0x20000000);
    result = *(int *)((unsigned int)_sceCd_scmdrdata | 0x20000000);
    SignalSema(_sceCd_scmd_semid);
    return result;
}
