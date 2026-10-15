/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 15 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01A798.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151E2C[];
extern int D_00151E24[];
extern int D_00151900[];

int  func_001220B0(int key);
void func_00107020(int a0);
void func_00107000(int a0);

int func_0011A798(int a0, int a1) {
    int id;

    if (D_00135630[0] == 0)
        return 0x81018001;
    id = func_001220B0(a0);
    if (id < 0)
        return 0x81018002;
    func_00107020(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        func_00107000(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900[0] = id;
    D_00151900[3] = a1;
    D_00151900[1] = 2;
    func_00107000(D_00151E24[0]);
    func_00107000(D_00151E2C[0]);
    return 0;
}
