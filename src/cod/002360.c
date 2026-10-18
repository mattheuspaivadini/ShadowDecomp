/* asm/cod/002360.s -> func_00102360.
 * $gp set by plain C on an int-typed _gp (gp = (void *)&_gp): -G8 marks the symbol small, so movsi emits one unsplit la insn instead of an asm; reorg can then move the thread-id copy over it into the next jal slot (Session 26).
 * MATCHED. */
struct RegInfo { int gpr[32][2]; int cop0[32][2]; };
extern struct RegInfo eeRegInfo;
extern int _gp;
register void *gp_reg asm ("$28");
extern char D_001368A0[];
extern char D_001368E0[];
int GetThreadId(void);
void LoaderSysExecuteRecoveryFirstProcess(void);
int ChangeThreadPriority(int thid, int prio);
int EIntr(void);
int LoaderSysPrintf(const char *fmt, ...);
int iGetCop0(int reg);
void LoaderSysJumpRecoverPointNoStateSetting(const char *fmt, ...);

void func_00102360(int a0, int epc, int cause, int a3, int a4, int (*regs)[4]) {
    int thid;
    int i;
    int (*q)[4];
    thid = GetThreadId();
    gp_reg = (void *)&_gp;
    LoaderSysExecuteRecoveryFirstProcess();
    ChangeThreadPriority(thid, 0x7F);
    EIntr();
    LoaderSysPrintf(D_001368A0, thid);
    q = regs;
    for (i = 0; i < 32; i++) {
        eeRegInfo.gpr[i][0] = q[i][0];
        eeRegInfo.cop0[i][0] = iGetCop0(i);
    }
    eeRegInfo.cop0[13][0] = epc;
    eeRegInfo.cop0[14][0] = cause;
    LoaderSysJumpRecoverPointNoStateSetting(D_001368E0);
}
