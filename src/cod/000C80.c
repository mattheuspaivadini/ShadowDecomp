/* asm/cod/000C80.s -> LoaderSysJumpRecoverPoint.
 * LoaderSysJumpRecoverPoint; $gp via a global register variable, re-entry address taken from the absolute symbol D_00100CD0 (a &&label is placed before the prologue by ee-gcc2.96), varargs into vsprintf (Session 23)
 * MATCHED. */
#include "stdarg.h"

struct RegInfo { int gpr[32][2]; int cop0[32][2]; };
extern struct RegInfo eeRegInfo;
extern char D_0013B348[];
register void *gp_reg asm ("$28");
void LoaderSysExecuteRecoveryFirstProcess(void);
extern char D_00100CD0[];   /* re-entry point (right before the first call); address from undefined_syms_auto.txt */
int func_0012C048(char *buf, const char *fmt, va_list ap);   /* vsprintf */
void func_00100A58(void);

void LoaderSysJumpRecoverPoint(const char *fmt, ...) {
    va_list ap;
    int i;
    void *pc;
    int ret;
    register int ra asm ("$31");
    register int sp asm ("$29");

    __asm__ ("la %0, _gp" : "=r" (gp_reg));
    LoaderSysExecuteRecoveryFirstProcess();
    va_start(ap, fmt);
    func_0012C048(D_0013B348, fmt, ap);
    va_end(ap);
    pc = D_00100CD0;
    ret = ra;
    for (i = 63; i >= 0; i--)
        ((int (*)[2])&eeRegInfo)[i][0] = 0;
    eeRegInfo.cop0[14][0] = (int)pc;
    eeRegInfo.gpr[31][0] = ret;
    eeRegInfo.gpr[29][0] = sp;
    func_00100A58();
}
