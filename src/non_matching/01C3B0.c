/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 21 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01C3B0.s); this C
 * draft (Session 9) is kept for the record. */
struct R01C3B0 {
    char pad000[0x400];
    int  arr[0x100];    /* 0x400 */
    int  f800;          /* 0x800 */
    char pad804[0x90];  /* 0x804 */
    int  f894;          /* 0x894 */
};

extern struct R01C3B0 D_0015DF48[];   /* .bss 0x0015DF48, 0x898-byte records */

int func_0011C200(int a0, int a1, int a2);
int func_0011C320(int index);
int _sceMcpReadClust(int index, int a1, int a2, int a3);

int func_0011C3B0(int a0, int a1, int *a2) {
    int off;
    int r;
    int v;

    off = a1 % 256;
    r = func_0011C200(a0, a1, (int)a2);
    if (*a2 != 0)
        return 0;
    if (D_0015DF48[a0].f800 != r) {
        if (func_0011C320(a0) == 0) {
            *a2 = 0x8101006F;
            return 0;
        }
        if (_sceMcpReadClust(a0, (int)D_0015DF48 + 0x400 + a0 * 0x898, r, 1) == 0) {
            *a2 = 0x8101006F;
            return 0;
        }
        D_0015DF48[a0].f800 = r;
    }
    v = D_0015DF48[a0].arr[off];
    *a2 = 0;
    return v;
}
