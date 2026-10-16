/* asm/cod/01A518.s -> func_00107020.
 * session9 R1 w25b wave
 * MATCHED (Session 8). */
int WaitSema(int a0);
int SignalSema(int a0);
int sceDbcSearchPortSpecific(int *rec);
extern int D_00135630[];
extern int D_00151904[];
extern int D_00151E2C[];

int sceMc2SearchSocket(int a0, int a1) {
    int rec[12];
    int r;

    if (D_00135630[0] == 0)
        return 0x81018001;
    if (D_00151904[0] != 0)
        return 0x81010010;
    WaitSema(D_00151E2C[0]);
    rec[2] = a0;
    rec[3] = a1;
    r = sceDbcSearchPortSpecific(rec);
    if (r < 0) {
        SignalSema(D_00151E2C[0]);
        return 0x81018002;
    }
    SignalSema(D_00151E2C[0]);
    return r;
}
