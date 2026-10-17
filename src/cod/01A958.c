/* asm/cod/01A958.s -> sceMc2GetDirAllAsync.
 * SCE libmc2 async command post (parameter reused for the socket id; strcpy = func_00128FB0)
 * MATCHED. */
int _sceMcCoreChangeSocketTypeDbc2Mc(int a0);
int WaitSema(int a0);
int SignalSema(int a0);
extern int D_00135630[];
extern int D_00151900[];
extern int D_00151E24[];
extern int D_00151E2C[];

int sceMc2GetDirAllAsync(int a0) {

    if (D_00135630[0] == 0)
        return 0x81018001;
    a0 = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (a0 < 0)
        return 0x81018002;
    WaitSema(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900[0] = a0;
    D_00151900[1] = 0x64;
    SignalSema(D_00151E24[0]);
    SignalSema(D_00151E2C[0]);
    return 0;
}
