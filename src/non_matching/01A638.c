/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 27 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01A638.s); this C
 * draft (Session 9) is kept for the record. */
int func_001220B0(int a0);
int func_00107020(int a0);
int func_00107000(int a0);
extern int D_00135630[];
extern int D_00151900[];
extern int D_00151E24[];
extern int D_00151E2C[];

int func_0011A638(int a0) {
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    r = func_001220B0(a0);
    if (r < 0)
        return 0x81018002;
    func_00107020(D_00151E2C[0]);
    if (D_00151900[1] != 0) {
        func_00107000(D_00151E2C[0]);
        return 0x81010010;
    }
    func_00107000(D_00151E24[0]);
    D_00151900[0] = r;
    D_00151900[1] = 3;
    func_00107000(D_00151E2C[0]);
    return 0;
}
