/* asm/cod/01A518.s -> func_00107020.
 * session9 R1 w25b wave
 * MATCHED (Session 8). */
int func_00107020(int a0);
int func_00107000(int a0);
int func_001164A8(int *rec);
extern int D_00135630[];
extern int D_00151904[];
extern int D_00151E2C[];

int func_0011A518(int a0, int a1) {
    int rec[12];
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    if (D_00151904[0] != 0)
        return 0x81010010;
    func_00107020(D_00151E2C[0]);
    rec[2] = a0;
    rec[3] = a1;
    r = func_001164A8(rec);
    if (r < 0) {
        func_00107000(D_00151E2C[0]);
        return 0x81018002;
    }
    func_00107000(D_00151E2C[0]);
    return r;
}
