/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 17 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01A330.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00135630[];
extern int D_00151904[];
extern int D_00151E20[];   /* handles +0x0 / +0x4 / +0x8 (lui/%lo) */
extern int D_00151E2C[];
extern char D_00138C68[];

int sceMc2Sync(int a0, int a1);
int TerminateThread(int a0);
void scePrintf(const char *msg);
void DeleteThread(int a0);
void DeleteSema(int a0);
void _sceMcCoreEnd(void);

int sceMc2End(void) {
    int a;

    if (D_00135630[0] == 0)
        return 0x81018001;
    if (D_00151904[0] != 0)
        sceMc2Sync(0, 0);
    a = D_00151E20[0];
    if (a >= 0) {
        if (TerminateThread(a) < 0)
            scePrintf(D_00138C68);
        DeleteThread(a);
    }
    if (D_00151E20[1] >= 0)
        DeleteSema(D_00151E20[1]);
    if (D_00151E20[2] >= 0)
        DeleteSema(D_00151E20[2]);
    if (D_00151E2C[0] >= 0)
        DeleteSema(D_00151E2C[0]);
    _sceMcCoreEnd();
    D_00135630[0] = 0;
    return 0;
}
