/* asm/cod/01A858.s -> sceMc2SearchFileAsync.
 * SCE libmc2 async command post (parameter reused for the socket id; strcpy = func_00128FB0)
 * MATCHED. */
extern int D_00135630[];
extern int D_00151E24[];
extern int D_00151E2C[];
extern int D_00151900[];

int _sceMcCoreChangeSocketTypeDbc2Mc(int key);
unsigned int func_001290C4(char *s);
void WaitSema(int sema);
void SignalSema(int sema);
char *func_00128FB0(char *dst, const char *src);   /* strcpy */

int sceMc2SearchFileAsync(int a0, char *a1, int a2) {
    char buf[0x200];

    if (D_00135630[0] == 0)
        return 0x81018001;
    a0 = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (a0 < 0)
        return 0x81018002;
    if (func_001290C4(a1) >= 0x80)
        return 0x8101005B;
    WaitSema(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900[0] = a0;
    D_00151900[1] = 0xE;
    func_00128FB0((char *)D_00151900 + 0x41C, a1);
    D_00151900[3] = a2;
    SignalSema(D_00151E24[0]);
    SignalSema(D_00151E2C[0]);
    return 0;
}
