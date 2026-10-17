/* asm/cod/010700.s -> StopTimerSystemTime.
 * timer StopTimerSystemTime; not-running arm first (Session 19)
 * MATCHED. */
#include "symbols.h"

int DIntr(void);
int EIntr(void);
void SetT2_MODE(unsigned int a0);

int StopTimerSystemTime(void) {
    int g;
    unsigned int mode;

    g = DIntr();
    mode = HWREG(EE_T2_MODE);
    if (!(mode & 0x80)) {
        if (g != 0)
            EIntr();
        return 0;
    }
    SetT2_MODE(mode & 0xFFFFF37Fu);
    if (g != 0)
        EIntr();
    return 1;
}
