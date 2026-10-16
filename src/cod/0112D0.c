/* asm/cod/0112D0.s -> func_001112D0 @ 0x001112D0
 * func_0010FB20(); then func_00111288(a0); then func_0010FB70() when the first
 * result is non-zero; the second result is returned. The single
 * trailing return is load-bearing: with an early return the `beqz`
 * targets the epilogue instead of the shared `v0 = b` copy (1 edit). */
int DIntr(void);
int iGetTimerBaseTime(int a0);
int EIntr(void);

int GetTimerBaseTime(int a0) {
    int a = DIntr();
    int b = iGetTimerBaseTime(a0);

    if (a != 0)
        EIntr();
    return b;
}
