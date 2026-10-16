/* asm/cod/010EA0.s -> func_00110EA0 @ 0x00110EA0
 * func_0010FB20(); then func_00110E00(a0); then func_0010FB70() when the first
 * result is non-zero; the second result is returned. The single
 * trailing return is load-bearing: with an early return the `beqz`
 * targets the epilogue instead of the shared `v0 = b` copy (1 edit). */
int DIntr(void);
int iFreeTimerCounter(int a0);
int EIntr(void);

int FreeTimerCounter(int a0) {
    int a = DIntr();
    int b = iFreeTimerCounter(a0);

    if (a != 0)
        EIntr();
    return b;
}
