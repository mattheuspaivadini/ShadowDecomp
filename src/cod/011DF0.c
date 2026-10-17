/* asm/cod/011DF0.s -> VSync2.
 * SCE VSync2; flag/value are written by the vsync handler (volatile) (Session 19)
 * MATCHED. */
#define EE_INTC_I_STAT 0x1000F000u
#define HWREG(addr) (*(volatile unsigned int *)(addr))

int  DIntr(void);
void EIntr(void);
void SetVSyncFlag(volatile int *flag, volatile long long *value);

long long VSync2(void) {
    volatile int flag;
    volatile long long value;
    int g;

    flag = 0;
    SetVSyncFlag(&flag, &value);
    g = DIntr();
    HWREG(EE_INTC_I_STAT) = 4;
    __asm__ __volatile__("sync" ::: "memory");
    if (g != 0)
        EIntr();
    while ((HWREG(EE_INTC_I_STAT) & 4) == 0 && flag == 0)
        ;
    g = DIntr();
    HWREG(EE_INTC_I_STAT) = 4;
    __asm__ __volatile__("sync" ::: "memory");
    if (g != 0)
        EIntr();
    return value;
}
