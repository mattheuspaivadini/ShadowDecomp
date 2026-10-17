/* asm/cod/014A20.s -> sceDmaPutEnv.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
typedef struct {
    unsigned char sts;          /* 0x00 */
    unsigned char std;          /* 0x01 */
    unsigned char mfd;          /* 0x02 */
    unsigned char rcycle;       /* 0x03 */
    unsigned short express;     /* 0x04 */
    unsigned short notify;      /* 0x06 */
    unsigned short sqwc;        /* 0x08 */
    unsigned short tqwc;        /* 0x0A */
    void *rbadr;                /* 0x0C */
    unsigned int rbmsk;         /* 0x10 */
} sceDmaEnv;

#define EE_D_CTRL 0x1000E000u
#define EE_D_PCR  0x1000E020u
#define EE_D_SQWC 0x1000E030u
#define EE_D_RBSR 0x1000E040u
#define EE_D_RBOR 0x1000E050u
#define HWREG(a) (*(volatile unsigned int *)(a))

extern const unsigned char D_00138530[];    /* sts selector -> D_CTRL.STS */
extern const unsigned char D_00138540[];    /* std selector -> D_CTRL.STD */
extern const unsigned char D_00138550[];    /* mfd selector -> D_CTRL.MFD */
extern sceDmaEnv D_0014B580;                /* current environment */

int sceDmaPutEnv(sceDmaEnv *env) {
    unsigned int ctrl;
    unsigned int pcr, sqwc, rbor, rbsr;

    ctrl = HWREG(EE_D_CTRL);
    pcr = HWREG(EE_D_PCR);
    sqwc = HWREG(EE_D_SQWC);
    rbor = HWREG(EE_D_RBOR);
    rbsr = HWREG(EE_D_RBSR);
    if (env->sts >= 10)
        return -1;
    if (env->std >= 10)
        return -2;
    if (env->mfd >= 10)
        return -3;
    if (env->rcycle >= 7)
        return -4;
    ctrl = (ctrl & ~0x30u) | (D_00138530[env->sts] << 4);
    ctrl = (ctrl & ~0xC0u) | (D_00138540[env->std] << 6);
    ctrl = (ctrl & ~0x0Cu) | (D_00138550[env->mfd] << 2);
    if (env->rcycle) {
        ctrl |= 2;
        ctrl = (ctrl & ~0x300u) | ((env->rcycle - 1) << 8);
    } else
        ctrl &= ~2u;
    pcr = (env->express << 16) | env->notify;
    sqwc = (env->tqwc << 16) | env->sqwc;
    rbor = (unsigned int)env->rbadr;
    rbsr = env->rbmsk;
    HWREG(EE_D_CTRL) = ctrl;
    HWREG(EE_D_PCR) = pcr;
    HWREG(EE_D_SQWC) = sqwc;
    HWREG(EE_D_RBOR) = rbor;
    HWREG(EE_D_RBSR) = rbsr;
    D_0014B580 = *env;
    return 0;
}
