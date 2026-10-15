/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 31 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01A858.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151E24[];
extern int D_00151E2C[];
extern int D_00151900[];

int func_001220B0(int key);
unsigned int func_001290C4(char *s);
void func_00107020(int sema);
void func_00107000(int sema);
void func_00128FB0(char *dst, char *src);

int func_0011A858(int a0, char *a1, int a2) {
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    r = func_001220B0(a0);
    if (r < 0)
        return 0x81018002;
    if (func_001290C4(a1) >= 0x80)
        return 0x8101005B;
    func_00107020(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        func_00107000(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900[0] = r;
    D_00151900[1] = 0xE;
    func_00128FB0((char *)D_00151900 + 0x41C, a1);
    D_00151900[3] = a2;
    func_00107000(D_00151E24[0]);
    func_00107000(D_00151E2C[0]);
    return 0;
}
