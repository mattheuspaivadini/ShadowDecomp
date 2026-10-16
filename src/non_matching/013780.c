/* STATUS (14, 2026-10-16): NON_MATCHING. best score 12 [cc=29].
 * sceGsPutDrawEnv: structure matches (58/58 insns) but residual = branch-likely bit on the timeout branch (orig bnez, mine bnezl) + the orig keeps a 0 = i copy at the loop head/delay slot (2 insns) and re-materialises the register base as lui+ori instead of lui+lw(-0x6000)
 * The original .s stays in the build (asm/cod/013780.s); this C
 * draft (14) is kept for the record. */
#include "symbols.h"

extern char D_001382E8[];   /* "sceGsPutDrawEnv: DMA Ch.2 does not terminate\r\n" */
extern int scePrintf(char *fmt, ...);

int sceGsPutDrawEnv(unsigned int GifPacket)
{
    unsigned int i;

    if ((HWREG(EE_D2_CHCR) & 0x100) != 0) {
        i = 0;
        do {
            if (i > 0x1000000u) {
                scePrintf(D_001382E8);
                return -1;
            }
            i++;
        } while ((HWREG(EE_D2_CHCR) & 0x100) != 0);
    }

    HWREG(EE_D2_QWC) = (int)(*(volatile unsigned long long *)GifPacket & 0x7FFF) + 1;
    if ((GifPacket & 0x70000000) == 0x70000000)
        HWREG(EE_D2_MADR) = (GifPacket & 0x0FFFFFFF) | 0x80000000;
    else
        HWREG(EE_D2_MADR) = GifPacket & 0x0FFFFFFF;
    HWREG(EE_D2_CHCR) = 0x101;
    return 0;
}
