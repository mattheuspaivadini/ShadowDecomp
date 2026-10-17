/* asm/cod/014940.s -> sceDmaReset.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
#include "symbols.h"

struct Strip0140 {
    int  f00;               /* 0x00 */
    char pad04[0xC];
    int  f10;               /* 0x10 */
    char pad14[0x1C];
    int  f30;               /* 0x30 */
    char pad34[0xC];
    int  f40;               /* 0x40 */
    char pad44[0xC];
    int  f50;               /* 0x50 */
    char pad54[0x2C];
    int  f80;               /* 0x80 */
};

extern int D_00138508[];    /* .data 0x00138508: per-channel "in use" flags */
extern int dch[];    /* .data 0x001339B0: per-channel strip pointers */

extern void func_001148E0(unsigned char *p, int n);
extern int sceDmaPutEnv(void *env);

int sceDmaReset(int a0) {
    unsigned int old;
    unsigned long long env[4];      /* 0x14 live bytes, 0x20-byte slot */
    volatile struct Strip0140 *p;
    int i;

    old = HWREG(EE_D_CTRL) & 1;
    for (i = 0; i < 10; i++) {
        if (D_00138508[i] != 0) {
            p = (volatile struct Strip0140 *)dch[i];
            p->f80 = 0;
            p->f00 = 0;
            p->f30 = 0;
            p->f10 = 0;
            p->f50 = 0;
            p->f40 = 0;
        }
    }
    HWREG(EE_D_STAT) = 0xFF1F;
    *(unsigned int *)EE_D_STAT = HWREG(EE_D_STAT) & 0xFF1F0000;
    func_001148E0((unsigned char *)env, 0x14);
    sceDmaPutEnv(env);
    if (a0 == 1)
        HWREG(EE_D_CTRL) = HWREG(EE_D_CTRL) | 1;
    return old;
}
