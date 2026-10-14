/* asm/cod/010EA0.s -> func_00110EA0 @ 0x00110EA0
 * func_0010FB20(); then func_00110E00(a0); then func_0010FB70() when the first
 * result is non-zero; the second result is returned. The single
 * trailing return is load-bearing: with an early return the `beqz`
 * targets the epilogue instead of the shared `v0 = b` copy (1 edit). */
int func_0010FB20(void);
int func_00110E00(int a0);
int func_0010FB70(void);

int func_00110EA0(int a0) {
    int a = func_0010FB20();
    int b = func_00110E00(a0);

    if (a != 0)
        func_0010FB70();
    return b;
}
