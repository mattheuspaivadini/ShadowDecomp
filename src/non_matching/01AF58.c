/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 17 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01AF58.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151E24[];
extern int D_00151E2C[];
extern int D_00151900[];

int _sceMcCoreChangeSocketTypeDbc2Mc(int key);
unsigned int func_001290C4(char *s);
void WaitSema(int sema);
void SignalSema(int sema);
void func_00128FB0(char *dst, char *src);

int sceMc2MkdirAsync(int a0, char *a1) {
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    r = _sceMcCoreChangeSocketTypeDbc2Mc(a0);
    if (r < 0)
        return 0x81018002;
    if (func_001290C4(a1) >= 0x80)
        return 0x8101005B;
    WaitSema(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900[0] = r;
    D_00151900[1] = 0xB;
    func_00128FB0((char *)D_00151900 + 0x41C, a1);
    D_00151900[3] = 0x8427;
    SignalSema(D_00151E24[0]);
    SignalSema(D_00151E2C[0]);
    return 0;
}
