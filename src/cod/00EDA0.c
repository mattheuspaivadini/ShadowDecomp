/* asm/cod/00EDA0.s -> func_0010EC78.
 * byte-exact under EE-GCC 2.95.3-136 (PE/wine)
 * MATCHED (Session 8). */
/* func_0010EDA0 @ 0x0010EDA0 (0x28 bytes): forwards (a0, &D_00138198,
 * a1, 1) to func_0010EC78. Second argument moves before its register is
 * reused. */
int func_0010EC78(int a, const char *b, int c, int d);

extern char D_00138198[];

void sceSifLoadElf(int a, int b) {
    func_0010EC78(a, D_00138198, b, 1);
}
