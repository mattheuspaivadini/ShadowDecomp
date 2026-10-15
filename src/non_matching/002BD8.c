/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 3 [cc=296].
 * R4 w25a_0: two-continue form (mirrors matched 002AF0)
 * The original .s stays in the build (asm/cod/002BD8.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int  func_00106ED0(void);
void func_00106E30(void);
void func_00106DF0(int a0);

void func_00102BD8(void) {
    int  i = 0xFF;
    int  value = -1;
    int  r;
    int *p;

    r = func_00106ED0();
    p = D_0013B790;
    for (; i >= 0; i--, p++) {
        if (*p == r)
            continue;
        if (*p < 0)
            continue;
        func_00106E30();
        func_00106DF0(*p);
        *p = value;
    }
}
