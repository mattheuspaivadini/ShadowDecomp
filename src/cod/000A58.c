/* asm/cod/000A58.s -> func_00100A58.
 * loader thread restart: gp/sp register variables, loaderThreadJumpCode label + patched jal emitted by asm, la for its address (Session 35)
 * MATCHED. */
extern char D_00139E50[];       /* .sdata "\n", addressed absolutely here */
extern char D_00136320[];       /* "in threadid: %d\n" */
extern char D_00136338[];
extern char D_00136378[];
extern char D_0013B348[];
extern int loaderThreadId;
extern void *spReg;
extern unsigned int loaderThreadJumpCode[];

register void *gp_reg asm ("$28");
register void *sp_reg asm ("$29");

int GetThreadId(void);
int ChangeThreadPriority(int thid, int prio);
void sceSifInitRpc(int mode);
int sceSifInitIopHeap(void);
int CancelWakeupThread(int thid);
int WakeupThread(int thid);
void SleepThread(void);
void PutString(int color, const char *fmt, ...);
int LoaderSysPrintf(const char *fmt, ...);
void LoaderSysSendAbort(void);
void loaderExecResetCallback(void);
unsigned int padSysReadForLoader(void);
void ExecBaseProc(void);
void Sync(void);
void loaderLoop(void);

void func_00100A58(void)
{
    int id;
    unsigned int *jc;
    unsigned int pad;

    id = GetThreadId();
    if (id == loaderThreadId) {
        ChangeThreadPriority(GetThreadId(), 1);
        sceSifInitRpc(0);
        sceSifInitIopHeap();
        __asm__ ("la %0, _gp" : "=r" (gp_reg));
        sp_reg = spReg;
        CancelWakeupThread(loaderThreadId);
        WakeupThread(loaderThreadId);
        __asm__ ("la %0, loaderThreadJumpCode" : "=r" (jc));
        jc = (unsigned int *)((unsigned int)jc | 0x20000000);
        *jc = (*jc & 0xFF000000) | ((unsigned int)loaderLoop >> 2);
        /* The jal patched above; the label is a global symbol other code references. */
        __asm__ __volatile__ (".globl loaderThreadJumpCode
.type loaderThreadJumpCode, @function\nloaderThreadJumpCode:\n\tjal 0\n\tnop");
    }
    ChangeThreadPriority(id, 0x7F);
    PutString(0xFF603000, D_00139E50);
    PutString(0xFF603000, D_00136320, id);
    PutString(0xFF603000, D_0013B348);
    PutString(0xC0FFE000, D_00136338);
    PutString(0xC0FFE000, D_00136378);
    LoaderSysPrintf(D_00139E50);
    LoaderSysSendAbort();
    loaderExecResetCallback();
    for (;;) {
        pad = padSysReadForLoader();
        ExecBaseProc();
        if (pad & 0x800)
            break;
        Sync();
    }
    PutString(0xFF603000, D_00139E50);
    ChangeThreadPriority(GetThreadId(), 0x7F);
    WakeupThread(loaderThreadId);
    while (1)
        SleepThread();
}
