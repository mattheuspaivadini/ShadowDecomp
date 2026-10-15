/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 36 [cc=296].
 * R2 w45a_0: rotated-loop (continue duplicating i++)
 * The original .s stays in the build (asm/cod/002500.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int func_00106FF0(int a0);
int func_00107050(int a0, int *a1);
extern int D_00131F80[];

void func_00102500(void) {
    int value = -1;
    int buf[8];
    int *p;
    int found;
    int t;
    int i;
    int j;

    p = D_0013BB90;
    for (i = 0xFF; i >= 0; i--) {
        if (*p >= 0) {
            func_00106FF0(*p);
            *p = value;
        }
        p++;
    }
    p = D_0013BB90;
    p += 0xFF;
    for (i = 0xFF; i >= 0; i--) {
        *p = value;
        p--;
    }
    for (i = 0; i < 0x100; i++) {
        found = 0;
        if (func_00107050(i, buf) == i) {
            t = buf[4];
            for (j = 0; j < 3; j++) {
                if (D_00131F80[j] == t) {
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
            continue;
        func_00106FF0(i);
    }
}
