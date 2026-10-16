/* asm/cod/010DB8.s -> func_00110DB8 @ 0x00110DB8
 * func_0010FB20(); then func_00110D48() *with no argument setup* (the asm has
 * a bare `jal` - the callee takes no arguments); if the first result is
 * non-zero, func_0010FB70(); the second result is returned. */
int DIntr(void);
int iAllocTimerCounter(void);
int EIntr(void);

int AllocTimerCounter(void) {
    int a = DIntr();
    int b = iAllocTimerCounter();

    if (a != 0)
        EIntr();
    return b;
}
