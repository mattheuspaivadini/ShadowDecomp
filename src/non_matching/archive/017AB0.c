/* ARCHIVED (Session 63, 2026-10-24): codegen-tuned attempt for 017AB0,
 * kept as the matching reference (it is the closest C form: see the STATUS
 * below).  The build now uses src/cod/017AB0.c, an instruction-stream
 * transcription; the readable reconstruction is
 * src/non_matching/017AB0.c.
 */
/* STATUS (Session 42, 2026-10-21): NON_MATCHING. best score 64 (was 76; sw.py diff lines).
 * Fence grid (build/s42/fence_grid.py: empty asm "+r" / asm volatile "r" use of each local after each statement): best single fence.
 * Rewritten on the 0175A8/017FB0 bind template: WriteBack/CallRpc inside the server-found branch (image layout: wait block after the failure return), rdata pointer live across CallRpc, the failure-path D_00133A64 = 0 through a volatile cast (stops loop.c from hoisting its %hi so fp holds hi(_sceCd_scmdrdata)), init order from a 500-permutation grid (169 -> 56 instructions). Residual: hi(D_00133A9C)/hi(D_00133A98) swap s4/s5 (priority .0877 vs .0851) and the c/b/a temp registers in the reply decode.
*/
struct SifRpcClientData {       /* 0x28 bytes */
    int  pad00[9];
    int  server;                /* 0x24 */
};

extern __attribute__((section(".data"))) int SCE_CD_debug;
extern __attribute__((section(".data"))) int _sceCd_ncmd_semid;
extern __attribute__((section(".data"))) int _sceCd_scmd_semid;
extern __attribute__((section(".data"))) int D_00133A60;
extern __attribute__((section(".data"))) int D_00133A64;
extern __attribute__((section(".data"))) int D_00133A7C;
extern __attribute__((section(".data"))) int D_00133A88;
extern __attribute__((section(".data"))) int D_00133A8C;
extern __attribute__((section(".data"))) int D_00133A90;
extern __attribute__((section(".data"))) int D_00133A94;
extern __attribute__((section(".data"))) int D_00133A98;
extern __attribute__((section(".data"))) int D_00133A9C;
extern __attribute__((section(".data"))) int _sceCd_ee_read_mode;
extern __attribute__((section(".data"))) int _sceCd_CdInit_ON;
extern struct SifRpcClientData D_00151028;
extern int D_00151080 __attribute__((section(".bss")));
extern int _sceCd_scmdrdata[];
extern char D_00138A00[];
extern char D_00138A20[];

void scePrintf(const char *fmt, ...);
void _sceCdInitSema(void);
int sceCdSyncS(int mode);
void sceSifInitRpc(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int request, int mode);
void sceSifWriteBackDCache(void *addr, int size);
int sceSifCallRpc(struct SifRpcClientData *cd, int rpc, int mode, void *send, int ssize, void *recv,
                  int rsize, void *end, void *param);
void func_00117098(void);
void func_00117210(void);

int sceCdInit(int mode) {
    int i;
    int r;
    int c;
    int b;
    int a;
    int *rd;

    if (sceCdSyncS(1) != 0)
        return 0;
    sceSifInitRpc(0);
    D_00133A64 = 1;
    D_00133A90 = -1;
    D_00133A8C = -1;
    D_00133A9C++;
    _sceCd_ee_read_mode = 0;
    D_00133A94 = -1;
    D_00133A88 = -1;
    D_00133A7C = -1;
    D_00133A98 = -1;
    while (1) {
        if ((b = sceSifBindRpc(&D_00151028, 0x80000592, 0)) < 0) {
            if (SCE_CD_debug > 0)
                scePrintf(D_00138A00, b, D_00133A9C);
            i = 0x100000;
            while (i--)
                ;
            continue;
        }
        if (D_00151028.server != 0) {
            D_00151080 = mode;
            D_00133A98 = 0;
            sceSifWriteBackDCache(&D_00151080, 4);
            rd = _sceCd_scmdrdata;
            if (sceSifCallRpc(&D_00151028, 0, 0, &D_00151080, 4, rd, 0x10, 0, 0) < 0) {
                *(volatile int *)&D_00133A64 = 0;
                return 0;
            }
            break;
        }
        i = 0x100000;
        while (i--)
            ;
    }
    c = *(int *)((unsigned int)&rd[3] | 0x20000000);
    b = *(int *)((unsigned int)&rd[1] | 0x20000000);
    asm("" : "+r"(b));
    a = *(int *)((unsigned int)&rd[2] | 0x20000000);
    r = 1;
    if (c != 0xFF) {
        if (c == 0xFE)
            SCE_CD_debug = 1;
        else if (b / 256 < 2 || a / 256 < 2)
            r = 2;
    }
    D_00133A64 = 0;
    switch (mode) {
    case 5:
        if (SCE_CD_debug > 0)
            scePrintf(D_00138A20);
        func_00117098();
        _sceCd_ncmd_semid = -1;
        _sceCd_scmd_semid = -1;
        D_00133A60 = -1;
        _sceCd_CdInit_ON = 0;
        break;
    case 0:
    case 1:
    default:
        _sceCdInitSema();
        func_00117210();
        _sceCd_CdInit_ON = 1;
        break;
    }
    return r;
}
