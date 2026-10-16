/* asm/cod/011050.s -> func_00111050 @ 0x00111050
 * func_0010FB20(); then func_00110FA0(a0); then func_0010FB70() when the first
 * result is non-zero; the second result is returned. The single
 * trailing return is load-bearing: with an early return the `beqz`
 * targets the epilogue instead of the shared `v0 = b` copy (1 edit). */
int DIntr(void);
int iStartTimerCounter(int a0);
int EIntr(void);

int StartTimerCounter(int a0) {
    int a = DIntr();
    int b = iStartTimerCounter(a0);

    if (a != 0)
        EIntr();
    return b;
}
