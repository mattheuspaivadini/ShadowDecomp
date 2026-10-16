/* asm/cod/002AF0.s -> func_00106ED0.
 * clean; wave3e (R1)
 * MATCHED (Session 8). */
#include "symbols.h"

int  GetThreadId(int a0);
void ChangeThreadPriority(int a0, int a1);

void LoaderSysChangeExteranalThreadPriorityExceptMe(int a0) {
    int  i;
    int  r;
    int *p;

    r = GetThreadId(a0);
    for (i = 0xFF, p = D_0013B790; i >= 0; i--, p++) {
        if (*p == r)
            continue;
        if (*p < 0)
            continue;
        ChangeThreadPriority(*p, a0);
    }
}
