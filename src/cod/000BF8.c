/* asm/cod/000BF8.s -> LoaderSysJumpRecoverPointNoStateSetting.
 * LoaderSysJumpRecoverPoint (000C80) without the eeRegInfo state capture: $gp via a global register variable, varargs into vsprintf (Session 28).
 * MATCHED. */
#include "stdarg.h"

extern char D_0013B348[];
register void *gp_reg asm ("$28");
void LoaderSysExecuteRecoveryFirstProcess(void);
int func_0012C048(char *buf, const char *fmt, va_list ap);   /* vsprintf */
void func_00100A58(void);

void LoaderSysJumpRecoverPointNoStateSetting(const char *fmt, ...) {
    va_list ap;

    __asm__ ("la %0, _gp" : "=r" (gp_reg));
    LoaderSysExecuteRecoveryFirstProcess();
    va_start(ap, fmt);
    func_0012C048(D_0013B348, fmt, ap);
    va_end(ap);
    func_00100A58();
}
