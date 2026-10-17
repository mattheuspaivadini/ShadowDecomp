/* asm/cod/010CC8.s -> GetTimerSystemTime.
 * timer GetTimerSystemTime; DIntr-guarded inline-asm time read (Session 19)
 * MATCHED. */
#include "ee_timer.h"


int DIntr(void);
int EIntr(void);

unsigned long GetTimerSystemTime(void) {
    unsigned long r;
    int g;

    g = DIntr();
    TIMER_SYSTEM_TIME(r);
    if (g != 0)
        EIntr();
    return r;
}
