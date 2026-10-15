/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 3 [cc=29].
 * R4 w25a_1: s2 counter 2->3 with s1+=8 strength reduction
 * The original .s stays in the build (asm/cod/00FF00.s); this C
 * draft (Session 8) is kept for the record. */
int func_0010FE98(void);
int func_0010FE88(void);
void func_0010FE30(int a0, int a1);
void func_0010FE40(int a0, int *a1, int a2);
void func_00107260(int a0);

extern int D_00133150[];
extern int D_001329A8[];

void func_0010FF00(void) {
    int *q;
    unsigned int i;

    if (func_0010FE98() == 0)
        return;
    func_0010FE30(D_00133150[0], D_00133150[1]);
    func_0010FE40(0x80074000, D_001329A8, 0x7A8);
    func_00107260(0);
    func_00107260(2);
    func_0010FE30(D_00133150[2], D_00133150[3]);
    q = &D_00133150[4];
    for (i = 2; i < 3; i++)
        func_0010FE30(q[(i - 2) * 2], func_0010FE88());
}
