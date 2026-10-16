/* asm/cod/01A498.s -> func_001220B0.
 * session9 R1 w25b wave
 * MATCHED (Session 8). */
int _sceMcCoreChangeSocketTypeDbc2Mc(int a0);
int _sceMcCoreDeleteSocket(int a0);
extern int D_00135630[];
extern int D_00151904[];

int sceMc2DeleteSocket(int a0) {
    int idx;

    idx = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (idx < 0)
        return 0x81018002;
    if (D_00135630[0] == 0)
        return 0x81018001;
    if (D_00151904[0] != 0)
        return 0x81010010;
    return _sceMcCoreDeleteSocket(idx) != 0 ? 0 : 0x81018002;
}
