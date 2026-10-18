/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 1 [cc=296] (was 41).
 * Instruction-identical under the relocation-masked compare (verify_fast 0), but the link FAILS the hash: ee-gcc2.96 emits the &&resume label before the prologue (address 0x100C80) instead of at the jal (0x100CD0), whatever precedes it (volatile/non-volatile gp asm, va_start, goto). ee-gcc2.9 places it correctly but with a different frame. Counted as 1 (one lo16 word).
 * The original .s stays in the build (asm/cod/000C80.s); this C
 * draft (Session 23) is kept for the record. */
#include "stdarg.h"

struct RegInfo { int gpr[32][2]; int cop0[32][2]; };
extern struct RegInfo eeRegInfo;
extern char D_0013B348[];
register void *gp_reg asm ("$28");
void LoaderSysExecuteRecoveryFirstProcess(void);
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
resume:
    LoaderSysExecuteRecoveryFirstProcess();
    va_start(ap, fmt);
    func_0012C048(D_0013B348, fmt, ap);
    va_end(ap);
    pc = &&resume;
    ret = ra;
    for (i = 63; i >= 0; i--)
        ((int (*)[2])&eeRegInfo)[i][0] = 0;
    eeRegInfo.cop0[14][0] = (int)pc;
    eeRegInfo.gpr[31][0] = ret;
    eeRegInfo.gpr[29][0] = sp;
    func_00100A58();
}
