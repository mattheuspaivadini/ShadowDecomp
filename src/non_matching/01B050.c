/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 20 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01B050.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151E24[];
extern int D_00151E2C[];
extern int D_00151900 __attribute__((section(".data")));   /* non-small scalar */

int _sceMcCoreChangeSocketTypeDbc2Mc(int a0);
int func_001290C4(char *s);
void WaitSema(int a0);
void SignalSema(int a0);
void func_00128FB0(char *dst, char *src);

int sceMc2ChdirAsync(int a0, int a1, int a2) {
    int *rec;
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    r = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (r < 0)
        return 0x81018002;
    if ((unsigned int)func_001290C4((char *)a1) >= 0x80)
        return 0x8101005B;
    WaitSema(D_00151E2C[0]);
    rec = &D_00151900;
    if (rec[1] != 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900 = r;
    rec[1] = 0xC;
    func_00128FB0((char *)rec + 0x41C, (char *)a1);
    rec[3] = a2;
    SignalSema(D_00151E24[0]);
    SignalSema(D_00151E2C[0]);
    return 0;
}
