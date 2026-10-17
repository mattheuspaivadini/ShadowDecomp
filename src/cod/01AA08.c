/* asm/cod/01AA08.s -> sceMc2ReadFileAsync.
 * SCE libmc2 async command post (parameter reused for the socket id; strcpy = func_00128FB0)
 * MATCHED. */
extern int D_00135630[];
extern int D_00151E24[];
extern int D_00151E2C[];
extern int D_00151900[];

int _sceMcCoreChangeSocketTypeDbc2Mc(int a0);
int func_001290C4(char *s);
void WaitSema(int a0);
void SignalSema(int a0);
char *func_00128FB0(char *dst, const char *src);   /* strcpy */

int sceMc2ReadFileAsync(int a0, int a1, int a2, int a3, int a4) {
    int *rec;

    if (D_00135630[0] == 0)
        return 0x81018001;
    a0 = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (a0 < 0)
        return 0x81018002;
    if ((unsigned int)func_001290C4((char *)a1) >= 0x80)
        return 0x8101005B;
    WaitSema(D_00151E2C[0]);
    rec = D_00151900;
    if (rec[1] != 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81010010;
    }
    rec[0] = a0;
    rec[1] = 5;
    func_00128FB0((char *)rec + 0x41C, (char *)a1);
    rec[3] = a2;
    rec[4] = a3;
    rec[5] = a4;
    SignalSema(D_00151E24[0]);
    SignalSema(D_00151E2C[0]);
    return 0;
}
