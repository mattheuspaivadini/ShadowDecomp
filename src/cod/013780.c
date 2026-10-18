/* asm/cod/013780.s -> sceGsPutDrawEnv.
 * sceGsPutDrawEnv; DMA Ch.2 wait as while + post-increment timeout (Session 22)
 * MATCHED. */
#include "symbols.h"

extern char D_001382E8[];   /* "sceGsPutDrawEnv: DMA Ch.2 does not terminate\r\n" */
extern int scePrintf(char *fmt, ...);

int sceGsPutDrawEnv(unsigned int GifPacket)
{
    unsigned int i;

    i = 0;
    while ((HWREG(EE_D2_CHCR) & 0x100) != 0) {
        if (i++ > 0x1000000) {
            scePrintf(D_001382E8);
            return -1;
        }
    }

    HWREG(EE_D2_QWC) = (int)(*(volatile unsigned long long *)GifPacket & 0x7FFF) + 1;
    if ((GifPacket & 0x70000000) == 0x70000000)
        HWREG(EE_D2_MADR) = (GifPacket & 0x0FFFFFFF) | 0x80000000;
    else
        HWREG(EE_D2_MADR) = GifPacket & 0x0FFFFFFF;
    HWREG(EE_D2_CHCR) = 0x101;
    return 0;
}
