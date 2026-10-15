/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 20 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01B150.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151E24[];
extern int D_00151E2C[];
extern int D_00151900 __attribute__((section(".data")));   /* non-small scalar */

int func_001220B0(int a0);
int func_001290C4(char *s);
void func_00107020(int a0);
void func_00107000(int a0);
void func_00128FB0(char *dst, char *src);

int func_0011B150(int a0, int a1, int a2) {
    int *rec;
    int r;
    int v;

    v = a2 & 0xFFFF;
    if (D_00135630[0] == 0)
        return 0x81018001;
    r = func_001220B0(a0);
    if (r < 0)
        return 0x81018002;
    if ((unsigned int)func_001290C4((char *)a1) >= 0x80)
        return 0x8101005B;
    func_00107020(D_00151E2C[0]);
    rec = &D_00151900;
    if (rec[1] != 0) {
        func_00107000(D_00151E2C[0]);
        return 0x81010010;
    }
    D_00151900 = r;
    rec[1] = 0xD;
    func_00128FB0((char *)rec + 0x41C, (char *)a1);
    rec[3] = v;
    func_00107000(D_00151E24[0]);
    func_00107000(D_00151E2C[0]);
    return 0;
}
