/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 17 [cc=29].
 * R4 w25a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/011E98.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int sceTtyInit(int a0);
int sceTtyWrite(int a0, int a1);

int write(int a0, int a1, int a2) {
    if ((unsigned int)(a0 - 1) >= 2)
        return -1;
    if (D_00133940 == 0) {
        if (sceTtyInit(a1) == 0)
            return -1;
        D_00133940 = 1;
    }
    return sceTtyWrite(a1, a2);
}
