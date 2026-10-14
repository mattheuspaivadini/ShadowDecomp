/* asm/cod/00F118.s -> func_0010F118 @ 0x0010F118
 * If func_001073F0(4) has bit 0x40000 set: func_00111D50(), then
 * func_00111CA8(1, 1) and func_00111CA8(0, 1); returns 1. Otherwise 0.
 * The result must be held in a named local - testing the call expression
 * directly makes ee-gcc `and` into $a0 instead of $v0 (2 edits). */
int func_001073F0(int a0);
int func_00111D50(void);
int func_00111CA8(int a0, int a1);

int func_0010F118(void) {
    int r = func_001073F0(4);

    if ((r & 0x40000) == 0)
        return 0;
    func_00111D50();
    func_00111CA8(1, 1);
    func_00111CA8(0, 1);
    return 1;
}
