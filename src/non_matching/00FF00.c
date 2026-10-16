/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 3 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/00FF00.s); this C
 * draft (Session 9) is kept for the record. */
int func_0010FE98(void);
int func_0010FE88(void);
void func_0010FE30(int a0, int a1);
void func_0010FE40(int a0, int *a1, int a2);
void FlushCache(int a0);

extern int SysExecPS2Entry[];
extern int D_001329A8[];

void InitExecPS2(void) {
    int         *q;
    unsigned int i;

    if (func_0010FE98() == 0)
        return;
    func_0010FE30(SysExecPS2Entry[0], SysExecPS2Entry[1]);
    func_0010FE40(0x80074000, D_001329A8, 0x7A8);
    FlushCache(0);
    FlushCache(2);
    func_0010FE30(SysExecPS2Entry[2], SysExecPS2Entry[3]);
    q = &SysExecPS2Entry[4];
    for (i = 2; i < 3; i++) {
        func_0010FE30(*q, func_0010FE88());
        q += 2;
    }
}
