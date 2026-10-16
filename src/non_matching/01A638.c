/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 27 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01A638.s); this C
 * draft (Session 9) is kept for the record. */
int _sceMcCoreChangeSocketTypeDbc2Mc(int a0);
int WaitSema(int a0);
int SignalSema(int a0);
extern int D_00135630[];
extern int D_00151900[];
extern int D_00151E24[];
extern int D_00151E2C[];

int sceMc2FormatAsync(int a0) {
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    r = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (r < 0)
        return 0x81018002;
    WaitSema(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81010010;
    }
    SignalSema(D_00151E24[0]);
    D_00151900[0] = r;
    D_00151900[1] = 3;
    SignalSema(D_00151E2C[0]);
    return 0;
}
