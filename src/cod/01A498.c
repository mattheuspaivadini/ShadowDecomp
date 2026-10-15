/* asm/cod/01A498.s -> func_001220B0.
 * session9 R1 w25b wave
 * MATCHED (Session 8). */
int func_001220B0(int a0);
int func_00122048(int a0);
extern int D_00135630[];
extern int D_00151904[];

int func_0011A498(int a0) {
    int idx;

    idx = func_001220B0(a0);
    if (idx < 0)
        return 0x81018002;
    if (D_00135630[0] == 0)
        return 0x81018001;
    if (D_00151904[0] != 0)
        return 0x81010010;
    return func_00122048(idx) != 0 ? 0 : 0x81018002;
}
