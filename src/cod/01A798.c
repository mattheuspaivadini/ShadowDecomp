/* asm/cod/01A798.s -> sceMc2GetInfoAsync.
 * SCE libmc2 async command post (parameter reused for the socket id; strcpy = func_00128FB0)
 * MATCHED. */
extern int D_00135630[];
extern int D_00151E2C[];
extern int D_00151E24[];
extern int D_00151900[];

int  _sceMcCoreChangeSocketTypeDbc2Mc(int key);
void WaitSema(int a0);
void SignalSema(int a0);

int sceMc2GetInfoAsync(int a0, int a1) {
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
    D_00151900[1] = 2;
    D_00151900[3] = a1;
    SignalSema(D_00151E24[0]);
    SignalSema(D_00151E2C[0]);
    return 0;
}
