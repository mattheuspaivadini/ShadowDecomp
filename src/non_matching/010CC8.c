/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 30 [cc=296].
 * R4 w25a_1: inner body identical to non-matching 010C78
 * The original .s stays in the build (asm/cod/010CC8.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int func_0010FB20(void);
int func_0010FB70(void);

struct T133918 {
    unsigned long long base;    /* 0x00 time base */
    char pad[0x18];
};

extern struct T133918 D_00133918;

unsigned long long func_00110CC8(void) {
    volatile unsigned int *t2;
    unsigned int count;
    unsigned int mode;
    unsigned int src;
    unsigned long long value;
    unsigned long long scale;
    int g;

    g = func_0010FB20();
    t2 = (volatile unsigned int *)0x10001000;
    count = t2[0];
    mode = t2[4];
    value = D_00133918.base;
    if (mode & 0x800) {
        count = t2[0];
        value = value + 1;
    }
    src = mode & 3;
    value = count | (value << 16);
    scale = 2;
    if (src == 0)
        scale = 0;
    if (g != 0)
        func_0010FB70();
    return value << (scale << src);
}
