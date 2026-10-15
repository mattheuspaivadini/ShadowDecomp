/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 10 [cc=296].
 * R4 w25a_0: buf[0..2] store order
 * The original .s stays in the build (asm/cod/004DF8.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int func_00115008(int a0);
int func_001150B0(int *args, void *p);

void func_00104DF8(void) {
    int   buf[3];
    int   i;
    char *p;

    func_00115008(0);
    p = D_0013D840;
    for (i = 0; i < 2; i++) {
        buf[0] = 2;
        buf[1] = (i != 0);
        buf[2] = 0;
        *(int *)(p + 0x11C) = func_001150B0(buf, p);
        *(int *)(p + 0x120) = 0;
        p += 0x140;
    }
}
