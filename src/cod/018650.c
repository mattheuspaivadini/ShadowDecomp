/* asm/cod/018650.s -> sceInetName2Address.
 * SCE libinet; variadic (EABI a7 save at 0x88), optional arg via va_arg (Session 19)
 * MATCHED. */
#include "stdarg.h"
/* STATUS (10, 2026-10-16): NON_MATCHING. best score 6 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/018650.s); this C
 * draft (10) is kept for the record. */
struct S018650 {
    int f0;    /* 0x00 */
    int f4;    /* 0x04 */
    int f8;    /* 0x08 */
    int fC;    /* 0x0C */
    int f10;   /* 0x10 */
};

int func_001184E8(int a0, int *a1, int a2, char *a3);
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118490(int a0, int a1, int *p, int a3, int a4);

int sceInetName2Address(int a0, struct S018650 *p, int a2, int a3, char *a4, int a5,
                  int a6, ...) {
    va_list ap;
    int r;

    p->f4 = a5;
    p->f8 = a6;
    p->f0 = a2;
    p->fC = 0;
    va_start(ap, a6);
    if (a2 & 0x80)
        p->fC = va_arg(ap, int);
    va_end(ap);
    r = func_001184E8(a0, (int *)p, 5, a4);
    if (r < 0)
        return r;
    p->f10 = r;
    r = func_00118380(a0, 6, (int *)p, r + 0x14, 0x14);
    if (r < 0)
        return -0x21E;
    r = func_00118490(a0, a3, (int *)p, 1, 0x10);
    if (r >= 0)
        return p->f0;
    return r;
}
