/* asm/cod/011168.s -> func_00111168 @ 0x00111168
 * func_0010FB20(); then func_001110A0(a0); then func_0010FB70() when the first
 * result is non-zero; the second result is returned. The single
 * trailing return is load-bearing: with an early return the `beqz`
 * targets the epilogue instead of the shared `v0 = b` copy (1 edit). */
int DIntr(void);
int iStopTimerCounter(int a0);
int EIntr(void);

int StopTimerCounter(int a0) {
    int a = DIntr();
    int b = iStopTimerCounter(a0);

    if (a != 0)
        EIntr();
    return b;
}
