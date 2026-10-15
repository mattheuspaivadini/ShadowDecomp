/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=296].
 * R4 w25a_0: same body as matched 006430 + init + two .sbss stores
 * The original .s stays in the build (asm/cod/006498.s); this C
 * draft (Session 8) is kept for the record. */
#include "symbols.h"

struct E006498 {
    int           field00;   /* 0x00 */
    unsigned char field04;   /* 0x04 */
    char          pad05[3];  /* to 0x08 */
};

extern struct E006498 D_0013A160;    /* .sdata, gp-relative template record */
extern struct E006498 D_0013ED90[];  /* .bss: 40 rows x 60 records */
void func_00105CE0(void);

void func_00106498(void) {
    int i;
    int j;

    func_00105CE0();
    for (i = 0; i < 0x28; i++)
        for (j = 0; j < 0x3C; j++)
            D_0013ED90[i * 0x3C + j] = D_0013A160;
    D_0013A16C = 0;
    D_0013A170 = 0;
}
