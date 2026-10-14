/* asm/cod/002AF0.s -> func_00106ED0.
 * clean; wave3e (R1)
 * MATCHED (Session 8). */
#include "symbols.h"

int  func_00106ED0(int a0);
void func_00106E70(int a0, int a1);

void func_00102AF0(int a0) {
    int  i;
    int  r;
    int *p;

    r = func_00106ED0(a0);
    for (i = 0xFF, p = D_0013B790; i >= 0; i--, p++) {
        if (*p == r)
            continue;
        if (*p < 0)
            continue;
        func_00106E70(*p, a0);
    }
}
