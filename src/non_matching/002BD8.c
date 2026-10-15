/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 3 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/002BD8.s); this C
 * draft (Session 9) is kept for the record. */
#include "symbols.h"

int  func_00106ED0(void);
void func_00106E30(void);
void func_00106DF0(int a0);

void func_00102BD8(void) {
    int  value = -1;
    int  i;
    int  r;
    int *p;

    r = func_00106ED0();
    for (i = 0xFF, p = D_0013B790; i >= 0; i--, p++) {
        if (*p == r)
            continue;
        if (*p < 0)
            continue;
        func_00106E30();
        func_00106DF0(*p);
        *p = value;
    }
}
