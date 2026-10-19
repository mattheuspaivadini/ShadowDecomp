/* asm/cod/0178A8.s -> _sceCd_scmd_prechk.
 * libcdvd S-command precheck; twin of _sceCd_ncmd_prechk 0175A8 (bind 0x80000593, sceCdSyncS)
 * MATCHED. */
struct SifRpcClientData {       /* 0x28 bytes */
    int  pad00[9];
    int  server;                /* 0x24 */
};

extern __attribute__((section(".data"))) int SCE_CD_debug;
extern __attribute__((section(".data"))) volatile int _sceCd_scmd_semid;
extern __attribute__((section(".data"))) int D_00133A58;     /* function of the running command */
extern __attribute__((section(".data"))) int D_00133A94;     /* < 0 until the RPC server is bound */
extern struct SifRpcClientData _sceCd_cd_scmd;
extern char D_001389C0[];
extern char D_001389E8[];

void scePrintf(const char *fmt, ...);
void _sceCdInitSema(void);
int PollSema(int sema);
int SignalSema(int sema);
int sceCdSyncS(int mode);
void sceSifInitRpc(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int request, int mode);

int _sceCd_scmd_prechk(int func) {
    int i;

    _sceCdInitSema();
    if (_sceCd_scmd_semid != PollSema(_sceCd_scmd_semid)) {
        if (SCE_CD_debug > 0)
            scePrintf(D_001389C0, func, D_00133A58);
        return 0;
    }
    D_00133A58 = func;
    if (sceCdSyncS(1) != 0) {
        SignalSema(_sceCd_scmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_00133A94 >= 0)
        return 1;
    while (1) {
        if (sceSifBindRpc(&_sceCd_cd_scmd, 0x80000593, 0) < 0) {
            if (SCE_CD_debug > 0)
                scePrintf(D_001389E8);
            i = 0x100000;
            while (i--)
                ;
            continue;
        }
        if (_sceCd_cd_scmd.server != 0)
            break;
        i = 0x100000;
        while (i--)
            ;
    }
    D_00133A94 = 0;
    return 1;
}
