/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 7 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01AA08.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151E24[];
extern int D_00151E2C[];
extern int D_00151900[];

int func_001220B0(int a0);
int func_001290C4(char *s);
void func_00107020(int a0);
void func_00107000(int a0);
void func_00128FB0(char *dst, char *src);

int func_0011AA08(int a0, int a1, int a2, int a3, int a4) {
    int *rec;
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    r = func_001220B0(a0);
    if (r < 0)
        return 0x81018002;
    if ((unsigned int)func_001290C4((char *)a1) >= 0x80)
        return 0x8101005B;
    func_00107020(D_00151E2C[0]);
    rec = D_00151900;
    if (rec[1] != 0) {
        func_00107000(D_00151E2C[0]);
        return 0x81010010;
    }
    rec[0] = r;
    rec[1] = 5;
    func_00128FB0((char *)rec + 0x41C, (char *)a1);
    rec[3] = a2;
    rec[4] = a3;
    rec[5] = a4;
    func_00107000(D_00151E24[0]);
    func_00107000(D_00151E2C[0]);
    return 0;
}
