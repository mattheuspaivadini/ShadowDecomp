/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 14 [cc=29].
 * R1 wave4c: DMAC hold (D_ENABLER bit16)
 * The original .s stays in the build (asm/cod/014F58.s); this C
 * draft (Session 8) is kept for the record. */
#define EE_D_CTRL    0x1000E000u        /* DMAC control                      */
#define EE_D_ENABLER 0x1000F520u        /* DMAC disabled status (read)       */
#define EE_D_ENABLEW 0x1000F590u        /* DMAC disable (write)              */
#define HWREG(a) (*(volatile unsigned int *)(a))

int func_0010FB20(void);
int func_0010FB70(void);

int func_00114F58(unsigned int *a0) {
    int r = func_0010FB20();
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
        func_0010FB70();
    return v;
}
