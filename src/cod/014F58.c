/* asm/cod/014F58.s -> sceDmaPause.
 * SCE libvifpk/libdma (cc=29)
 * MATCHED. */
#define EE_D_CTRL    0x1000E000u        /* DMAC control                      */
#define EE_D_ENABLER 0x1000F520u        /* DMAC disabled status (read)       */
#define EE_D_ENABLEW 0x1000F590u        /* DMAC disable (write)              */
#define HWREG(a) (*(volatile unsigned int *)(a))

int DIntr(void);
int EIntr(void);

int sceDmaPause(volatile unsigned int *a0) {
    int r = DIntr();
    unsigned int en;
    unsigned int v;

    en = HWREG(EE_D_ENABLER);
    if ((en & 0x10000) == 0)
        HWREG(EE_D_ENABLEW) = en | 0x10000;
    (void)HWREG(EE_D_CTRL);
    v = *a0;
    *a0 = v & 0xFFFFFEFFu;
    HWREG(EE_D_ENABLEW) = en;
    if (r != 0)
        EIntr();
    return v;
}
