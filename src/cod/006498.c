/* asm/cod/006498.s -> InitDisp.
 * InitDisp; ReinitDisp + ClearDisplay body expanded inline (template reloaded through gp per cell) + cursor reset (Session 35)
 * MATCHED. */
#include "symbols.h"

struct E006498 {
    int           field00;   /* 0x00 */
    unsigned char field04;   /* 0x04 */
    char          pad05[3];  /* to 0x08 */
};

extern struct E006498 D_0013A160;    /* .sdata, gp-relative template record */
extern struct E006498 D_0013ED90[];  /* .bss: 40 rows x 60 records */
void ReinitDisp(void);

/* Same body as ClearDisplay (006430); the original expands it in place, so it is modelled as an inline copy. */
static __inline__ void ClearDisplay(void)
{
    int i;
    int j;

    for (i = 0; i < 0x28; i++)
        for (j = 0; j < 0x3C; j++)
            D_0013ED90[i * 0x3C + j] = D_0013A160;
}

void InitDisp(void) {
    ReinitDisp();
    ClearDisplay();
    D_0013A16C = 0;
    D_0013A170 = 0;
}
