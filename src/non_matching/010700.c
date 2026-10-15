/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=29].
 * R4 w25a_1: T2_MODE stop via the func_0010FB20 guard family
 * The original .s stays in the build (asm/cod/010700.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int func_0010FB20(void);
int func_0010FB70(void);
void func_00110410(unsigned int a0);

int func_00110700(void) {
    int g;
    unsigned int mode;

    g = func_0010FB20();
    mode = HWREG(EE_T2_MODE);
    if (mode & 0x80) {
        func_00110410(mode & 0xFFFFF37Fu);
        if (g != 0)
            func_0010FB70();
        return 1;
    }
    if (g != 0)
        func_0010FB70();
    return 0;
}
