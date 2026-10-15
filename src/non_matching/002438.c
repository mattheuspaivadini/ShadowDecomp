/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 37 [cc=296].
 * R2 w45a_0: second loop shape vs matched 0029C8
 * The original .s stays in the build (asm/cod/002438.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

void func_00107470(int a0);
void func_00106CE0(int a0, int a1);

struct Pair00102438 {
    int f0;     /* 0x00 */
    int f4;     /* 0x04 */
};

void func_00102438(void) {
    int value = -1;
    struct Pair00102438 *t = (struct Pair00102438 *)D_0013BF90;
    int *p;
    int i;

    for (i = 0; i < 0x100; i++) {
        if (t[i].f4 < 0)
            continue;
        func_00107470(t[i].f0);
        func_00106CE0(t[i].f0, t[i].f4);
        t[i].f4 = value;
        t[i].f0 = value;
    }
    p = (int *)D_0013BF90;
    for (i = 0xFF; i >= 0; i--) {
        p[1] = value;
        p[0] = value;
        p += 2;
    }
}
