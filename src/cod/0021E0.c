/* asm/cod/0021E0.s -> func_001021E0.
 * loader exception handler: dump GPR/COP0 into eeRegInfo, banner, func_00101EC0, jump to the recover point; 002360 template
 * MATCHED. */
struct RegInfo { int gpr[32][2]; int cop0[32][2]; };
extern struct RegInfo eeRegInfo;
extern int _gp;
register void *gp_reg asm ("$28");
extern char D_001367E0[];
extern char D_00139FF0[];
extern char D_00136818[];
extern char D_00136850[];
extern char D_00136880[];
int GetThreadId(void);
void LoaderSysExecuteRecoveryFirstProcess(void);
int ChangeThreadPriority(int thid, int prio);
int EIntr(void);
int LoaderSysPrintf(const char *fmt, ...);
int iGetCop0(int reg);
void PutString(int color, const char *s);
void func_00101EC0(int code, int cause, int epc, int a3, int a4, struct RegInfo *info, int a6);
void LoaderSysJumpRecoverPointNoStateSetting(const char *fmt, ...);

void func_001021E0(int a0, int cause, int epc, int a3, int a4, int (*regs)[4]) {
    int thid;
    int i;
    int code;
    int (*q)[4];

    code = ((unsigned int)cause >> 2) & 0xF;
    thid = GetThreadId();
    gp_reg = (void *)&_gp;
    LoaderSysExecuteRecoveryFirstProcess();
    ChangeThreadPriority(thid, 0x7F);
    EIntr();
    LoaderSysPrintf(D_001367E0, thid);
    q = regs;
    for (i = 0; i < 32; i++) {
        eeRegInfo.gpr[i][0] = q[i][0];
        eeRegInfo.cop0[i][0] = iGetCop0(i);
    }
    eeRegInfo.cop0[13][0] = cause;
    eeRegInfo.cop0[14][0] = epc;
    PutString(0xFFFFFF00, D_00139FF0);
    PutString(0xFF802000, D_00136818);
    PutString(0xFF802000, D_00136850);
    PutString(0xFF802000, D_00136818);
    PutString(0xFF603000, D_00139FF0);
    func_00101EC0(code, cause, epc, a3, a4, &eeRegInfo, 0);
    LoaderSysJumpRecoverPointNoStateSetting(D_00136880);
}
