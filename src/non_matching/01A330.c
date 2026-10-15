/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 17 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01A330.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151904[];
extern int D_00151E20[];   /* handles +0x0 / +0x4 / +0x8 (lui/%lo) */
extern int D_00151E2C[];
extern char D_00138C68[];

int func_0011B740(int a0, int a1);
int func_00106E30(int a0);
void func_00108EF8(const char *msg);
void func_00106DF0(int a0);
void func_00106FF0(int a0);
void func_00121118(void);

int func_0011A330(void) {
    int a;

    if (D_00135630[0] == 0)
        return 0x81018001;
    if (D_00151904[0] != 0)
        func_0011B740(0, 0);
    a = D_00151E20[0];
    if (a >= 0) {
        if (func_00106E30(a) < 0)
            func_00108EF8(D_00138C68);
        func_00106DF0(a);
    }
    if (D_00151E20[1] >= 0)
        func_00106FF0(D_00151E20[1]);
    if (D_00151E20[2] >= 0)
        func_00106FF0(D_00151E20[2]);
    if (D_00151E2C[0] >= 0)
        func_00106FF0(D_00151E2C[0]);
    func_00121118();
    D_00135630[0] = 0;
    return 0;
}
