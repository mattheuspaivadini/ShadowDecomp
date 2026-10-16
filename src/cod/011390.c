/* asm/cod/011390.s -> func_00111390 @ 0x00111390
 * func_0010FB20(); then func_00111320(a0); then func_0010FB70() when the first
 * result is non-zero; the second result is returned. The single
 * trailing return is load-bearing: with an early return the `beqz`
 * targets the epilogue instead of the shared `v0 = b` copy (1 edit). */
int DIntr(void);
int iGetTimerCount(int a0);
int EIntr(void);

int GetTimerCount(int a0) {
    int a = DIntr();
    int b = iGetTimerCount(a0);

    if (a != 0)
        EIntr();
    return b;
}
