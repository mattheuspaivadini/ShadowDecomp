/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 10 [cc=296].
 * R4 w25a_0: buf[0..2] store order
 * The original .s stays in the build (asm/cod/004DF8.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

int scePad2Init(int a0);
int scePad2CreateSocket(int *args, void *p);

void padsysInit(void) {
    int   buf[3];
    int   i;
    char *p;

    scePad2Init(0);
    p = D_0013D840;
    for (i = 0; i < 2; i++) {
        buf[0] = 2;
        buf[1] = (i != 0);
        buf[2] = 0;
        *(int *)(p + 0x11C) = scePad2CreateSocket(buf, p);
        *(int *)(p + 0x120) = 0;
        p += 0x140;
    }
}
