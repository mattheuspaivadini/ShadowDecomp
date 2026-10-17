/* STATUS (Session 19, 2026-10-17): NON_MATCHING. best score 4 [cc=29].
 * base pointer + q = p + 6; residual = load order of the third TLB pair and the loop compare register
 * The original .s stays in the build (asm/cod/00F3C8.s); this C
 * draft (Session 19) is kept for the record. */
int func_0010F3B8(int a0, int a1);
int func_0010F360(int a0, void *a1, int a2);
int FlushCache(int a0);
int func_0010F3A8(int a0);

extern int D_001326B8[];   /* lui/%lo -> non-small */
extern int _kExecArg[];   /* lui/%lo -> non-small */
extern int D_00132338[];   /* lui/addiu -> non-small */

void InitTLBFunctions(void) {
    unsigned int i;
    int *p;
    int *q;

    p = D_001326B8;
    q = p + 6;
    func_0010F3B8(p[0], p[1]);
    func_0010F360(0x80075000, D_00132338, 0x330);
    FlushCache(0);
    FlushCache(2);
    func_0010F3B8(p[2], p[3]);
    func_0010F3B8(p[4], p[5]);
    for (i = 3; i < 8; i++) {
        func_0010F3B8(q[0], func_0010F3A8(q[0]));
        q += 2;
    }
    _kExecArg[0] = func_0010F3A8(3);
}
