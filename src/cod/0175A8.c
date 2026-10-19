/* asm/cod/0175A8.s -> _sceCd_ncmd_prechk.
 * libcdvd N-command precheck: semaphore poll, sync, bind 0x80000595 with an empty busy-wait (R5900 short-loop nops come from the compiler); volatile semid
 * MATCHED. */
struct SifRpcClientData {       /* 0x28 bytes */
    int  pad00[9];
    int  server;                /* 0x24 */
};

extern __attribute__((section(".data"))) int SCE_CD_debug;
extern __attribute__((section(".data"))) volatile int _sceCd_ncmd_semid;
extern __attribute__((section(".data"))) int D_00133A5C;     /* function of the running command */
extern __attribute__((section(".data"))) int D_00133A7C;     /* < 0 until the RPC server is bound */
extern struct SifRpcClientData _sceCd_cd_ncmd;
extern char D_00138960[];
extern char D_00138988[];

void scePrintf(const char *fmt, ...);
void _sceCdInitSema(void);
int PollSema(int sema);
int SignalSema(int sema);
int sceCdSync(int mode);
void sceSifInitRpc(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int request, int mode);

int _sceCd_ncmd_prechk(int func) {
    int i;

    _sceCdInitSema();
    if (_sceCd_ncmd_semid != PollSema(_sceCd_ncmd_semid)) {
        if (SCE_CD_debug > 0)
            scePrintf(D_00138960, func, D_00133A5C);
        return 0;
    }
    D_00133A5C = func;
    if (sceCdSync(1) != 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    sceSifInitRpc(0);
    if (D_00133A7C >= 0)
        return 1;
    while (1) {
        if (sceSifBindRpc(&_sceCd_cd_ncmd, 0x80000595, 0) < 0) {
            if (SCE_CD_debug > 0)
                scePrintf(D_00138988);
            i = 0x100000;
            while (i--)
                ;
            continue;
        }
        if (_sceCd_cd_ncmd.server != 0)
            break;
        i = 0x100000;
        while (i--)
            ;
    }
    D_00133A7C = 0;
    return 1;
}
