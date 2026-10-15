/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 7 [cc=29].
 * R4 w25a_2: 2nd I_STAT store as lui $at,0x10010000; sw -0x1000
 * The original .s stays in the build (asm/cod/011DF0.s); this C
 * draft (Session 8) is kept for the record. */
#define EE_INTC_I_STAT 0x1000F000u
#define HWREG(addr) (*(volatile unsigned int *)(addr))

int  func_0010FB20(void);
void func_0010FB70(void);
void func_00107350(int *flag, long long *value);

long long func_00111DF0(void) {
    int flag;
    long long value;
    int g;

    flag = 0;
    func_00107350(&flag, &value);
    g = func_0010FB20();
    HWREG(EE_INTC_I_STAT) = 4;
    __asm__ __volatile__("sync" ::: "memory");
    if (g != 0)
        func_0010FB70();
    while ((HWREG(EE_INTC_I_STAT) & 4) == 0 && flag == 0)
        ;
    g = func_0010FB20();
    HWREG(EE_INTC_I_STAT) = 4;
    __asm__ __volatile__("sync" ::: "memory");
    if (g != 0)
        func_0010FB70();
    return value;
}
