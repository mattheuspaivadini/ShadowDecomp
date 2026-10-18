/* asm/cod/01A330.s -> sceMc2End.
 * sceMc2End; thread/sema handle struct (Session 23)
 * MATCHED. */
struct H { int thid; int sema0; int sema1; };
extern int D_00135630[];
extern int D_00151904[];
extern struct H D_00151E20;
extern int D_00151E2C[];
extern char D_00138C68[];
int sceMc2Sync(int mode, int *cmd);
int TerminateThread(int thid);
void scePrintf(const char *fmt, ...);
int DeleteThread(int thid);
int DeleteSema(int sid);
void _sceMcCoreEnd(void);

int sceMc2End(void) {
    if (D_00135630[0] == 0) return 0x81018001;
    if (D_00151904[0] != 0) sceMc2Sync(0, 0);
    if (D_00151E20.thid >= 0) {
        if (TerminateThread(D_00151E20.thid) < 0) scePrintf(D_00138C68);
        DeleteThread(D_00151E20.thid);
    }
    if (D_00151E20.sema0 >= 0) DeleteSema(D_00151E20.sema0);
    if (D_00151E20.sema1 >= 0) DeleteSema(D_00151E20.sema1);
    if (D_00151E2C[0] >= 0) DeleteSema(D_00151E2C[0]);
    _sceMcCoreEnd();
    D_00135630[0] = 0;
    return 0;
}
