/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 4 [cc=296] (was 29).
 * Exception-recovery entry: global register variable for $gp set with asm la (gives the a5 -> s1 -> s2 copy and the direct lui/addiu $gp), typed eeRegInfo gpr/cop0 tables, cop0[13]=epc / cop0[14]=cause. Residual = the thid move is emitted before the $gp asm instead of in the next jal slot (permute_stmts 600: no gain).
 * The original .s stays in the build (asm/cod/002360.s); this C
 * draft (Session 23) is kept for the record. */
struct RegInfo { int gpr[32][2]; int cop0[32][2]; };
extern struct RegInfo eeRegInfo;
extern char _gp[];
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
    __asm__ ("la %0, _gp" : "=r" (gp_reg));
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
