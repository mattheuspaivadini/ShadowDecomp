/* asm/cod/013BF8.s -> sceGsSyncPath.
 * sceGsSyncPath; shared timeout counter, error labels in source order, msg pinned to a0, void scePrintf, register-pinned plain dump reads (Session 35)
 * MATCHED. */
#include "symbols.h"

extern char D_00138318[];   /* "sceGsSyncPath: DMA Ch.1 does not terminate\r\n" */
extern char D_00138348[];
extern char D_00138358[];
extern char D_00138368[];
extern char D_00138378[];
extern char D_00138388[];
extern char D_00138398[];
extern char D_001383A8[];
extern char D_001383B8[];
extern char D_001383C8[];
extern char D_001383E0[];
extern char D_001383F8[];   /* "sceGsSyncPath: DMA Ch.2 does not terminate\r\n" */
extern char D_00138428[];   /* "sceGsSyncPath: VIF1 does not terminate\r\n" */
extern char D_00138458[];   /* "sceGsSyncPath: VU1 does not terminate\r\n" */
extern char D_00138480[];   /* "sceGsSyncPath: GIF does not terminate\r\n" */
extern void scePrintf(char *fmt, ...);

#define D1_CHCR   0x10009000u
#define D1_MADR   0x10009010u
#define D1_QWC    0x10009020u
#define D1_TADR   0x10009030u
#define D2_CHCR   0x1000A000u
#define D2_MADR   0x1000A010u
#define D2_QWC    0x1000A020u
#define D2_TADR   0x1000A030u
#define VIF1_STAT 0x10003C00u
#define GIF_STAT  0x10003020u

#define VU1_STAT(x) __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(x))
/* Plain (non-volatile) read whose address stays a lui/ori register, so it can fill the jal delay slot. */
#define REG(a) ({ unsigned int *_p = (unsigned int *)(a); __asm__("" : "+r"(_p)); *_p; })

int sceGsSyncPath(int mode, unsigned short timeout)
{
    unsigned int i;
    int ret;
    register char *msg asm("$4");
    int stat;

    i = 0;
    if (mode == 0) {
        while (HWREG(D1_CHCR) & 0x100) {
            if (i++ > 0x1000000) goto ch1_err;
        }
        while (HWREG(D2_CHCR) & 0x100) {
            if (i++ > 0x1000000) goto ch2_err;
        }
        while (HWREG(VIF1_STAT) & 0x1f000003) {
            if (i++ > 0x1000000) goto vif1_err;
        }
        VU1_STAT(stat);
        while (stat & 0x100) {
            if (i++ > 0x1000000) goto vu1_err;
            VU1_STAT(stat);
        }
        while (HWREG(GIF_STAT) & 0xc00) {
            if (i++ > 0x1000000) goto gif_err;
        }
        return 0;
    ch1_err:
        msg = D_00138318;
        goto dump;
    ch2_err:
        msg = D_001383F8;
        goto dump;
    vif1_err:
        msg = D_00138428;
        goto dump;
    vu1_err:
        msg = D_00138458;
        goto dump;
    gif_err:
        msg = D_00138480;
    dump:
        scePrintf(msg);
        scePrintf(D_00138348, REG(D1_CHCR));
        scePrintf(D_00138358, REG(D1_TADR));
        scePrintf(D_00138368, REG(D1_MADR));
        scePrintf(D_00138378, REG(D1_QWC));
        scePrintf(D_00138388, REG(D2_CHCR));
        scePrintf(D_00138398, REG(D2_TADR));
        scePrintf(D_001383A8, REG(D2_MADR));
        scePrintf(D_001383B8, REG(D2_QWC));
        scePrintf(D_001383C8, REG(VIF1_STAT));
        scePrintf(D_001383E0, REG(GIF_STAT));
        return -1;
    }
    ret = 0;
    if (HWREG(D1_CHCR) & 0x100)
        ret = 1;
    if (HWREG(D2_CHCR) & 0x100)
        ret |= 2;
    if (HWREG(VIF1_STAT) & 0x1f000003)
        ret |= 4;
    VU1_STAT(stat);
    if (stat & 0x100)
        ret |= 8;
    if (HWREG(GIF_STAT) & 0xc00)
        ret |= 0x10;
    return ret;
}
