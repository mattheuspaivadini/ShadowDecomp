/* asm/cod/01C578.s -> func_0011C200.
 * session9 R2 wave A 45-80 tier
 * MATCHED (Session 8). */
struct R01C578 {
    char pad000[0x400];
    int  arr[0x100];    /* 0x400 */
    int  f800;          /* 0x800 */
    char pad804[0x90];  /* 0x804 */
    int  f894;          /* 0x894 */
};

extern struct R01C578 D_0015DF48[];   /* .bss 0x0015DF48, 0x898-byte records */

int func_0011C200(int a0, int a1, int a2);
int func_0011C320(int index);
int _sceMcpReadClust(int index, int a1, int a2, int a3);

int func_0011C578(int a0, int a1, int a2, int *a3) {
    int off;
    int r;

    off = a1 % 256;
    r = func_0011C200(a0, a1, (int)a3);
    if (*a3 != 0)
        return 0;
    if (D_0015DF48[a0].f800 != r) {
        if (func_0011C320(a0) == 0) {
            *a3 = 0x8101006F;
            return 0;
        }
        if (_sceMcpReadClust(a0, (int)D_0015DF48 + 0x400 + a0 * 0x898, r, 1) == 0) {
            *a3 = 0x8101006F;
            return 0;
        }
        D_0015DF48[a0].f800 = r;
    }
    D_0015DF48[a0].arr[off] = a2;
    D_0015DF48[a0].f894 = 1;
    *a3 = 0;
    return 1;
}
