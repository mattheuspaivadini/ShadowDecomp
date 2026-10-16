/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=29].
 * R4 w25a_1: T2_MODE stop via the func_0010FB20 guard family
 * The original .s stays in the build (asm/cod/010700.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int DIntr(void);
int EIntr(void);
void SetT2_MODE(unsigned int a0);

int StopTimerSystemTime(void) {
    int g;
    unsigned int mode;

    g = DIntr();
    mode = HWREG(EE_T2_MODE);
    if (mode & 0x80) {
        SetT2_MODE(mode & 0xFFFFF37Fu);
        if (g != 0)
            EIntr();
        return 1;
    }
    if (g != 0)
        EIntr();
    return 0;
}
