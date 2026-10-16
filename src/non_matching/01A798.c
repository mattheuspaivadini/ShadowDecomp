/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 15 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01A798.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151E2C[];
extern int D_00151E24[];
extern int D_00151900[];

int  _sceMcCoreChangeSocketTypeDbc2Mc(int key);
void WaitSema(int a0);
void SignalSema(int a0);

int sceMc2GetInfoAsync(int a0, int a1) {
    int id;

    if (D_00135630[0] == 0)
        return 0x81018001;
    id = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (id < 0)
        return 0x81018002;
    WaitSema(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900[0] = id;
    D_00151900[3] = a1;
    D_00151900[1] = 2;
    SignalSema(D_00151E24[0]);
    SignalSema(D_00151E2C[0]);
    return 0;
}
