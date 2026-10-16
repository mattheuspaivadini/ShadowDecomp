/* asm/cod/00F118.s -> func_0010F118 @ 0x0010F118
 * If func_001073F0(4) has bit 0x40000 set: func_00111D50(), then
 * func_00111CA8(1, 1) and func_00111CA8(0, 1); returns 1. Otherwise 0.
 * The result must be held in a named local - testing the call expression
 * directly makes ee-gcc `and` into $a0 instead of $v0 (2 edits). */
int sceSifGetReg(int a0);
int sceResetttyinit(void);
int sceSifExecNotifyHandler(int a0, int a1);

int sceSifSyncIop(void) {
    int r = sceSifGetReg(4);

    if ((r & 0x40000) == 0)
        return 0;
    sceResetttyinit();
    sceSifExecNotifyHandler(1, 1);
    sceSifExecNotifyHandler(0, 1);
    return 1;
}
