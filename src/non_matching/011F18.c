/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 17 [cc=29].
 * R1 wave3e: guard + shared return -1 block
 * The original .s stays in the build (asm/cod/011F18.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int func_001127E0(int a0);
int func_00112710(int a0, int a1);

int func_00111F18(int a0, int a1, int a2) {
    if (a0 != 0)
        return -1;
    if (D_00133940 == 0) {
        if (func_001127E0(a1) == 0)
            return -1;
        D_00133940 = 1;
    }
    return func_00112710(a1, a2);
}
