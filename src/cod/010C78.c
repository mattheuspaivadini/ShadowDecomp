/* asm/cod/010C78.s -> iGetTimerSystemTime.
 * timer iGetTimerSystemTime; SDK inline-asm time read (include/ee_timer.h) (Session 19)
 * MATCHED. */
#include "ee_timer.h"


unsigned long iGetTimerSystemTime(void) {
    unsigned long r;

    TIMER_SYSTEM_TIME(r);
    return r;
}
