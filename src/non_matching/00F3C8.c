/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 11 [cc=29].
 * R2 w45a_3: reg-alloc (first D_001326B8 access form)
 * The original .s stays in the build (asm/cod/00F3C8.s); this C
 * draft (Session 8) is kept for the record. */
int func_0010F3B8(int a0, int a1);
int func_0010F360(int a0, void *a1, int a2);
int func_00107260(int a0);
int func_0010F3A8(int a0);

extern int D_001326B8[];   /* lui/%lo -> non-small */
extern int D_001326B0[];   /* lui/%lo -> non-small */
extern int D_00132338[];   /* lui/addiu -> non-small */

void func_0010F3C8(void) {
    unsigned int i;
    int *q;

    q = &D_001326B8[6];
    func_0010F3B8(D_001326B8[0], D_001326B8[1]);
    func_0010F360(0x80075000, D_00132338, 0x330);
    func_00107260(0);
    func_00107260(2);
    func_0010F3B8(D_001326B8[2], D_001326B8[3]);
    func_0010F3B8(D_001326B8[4], D_001326B8[5]);
    for (i = 3; i < 8; i++) {
        func_0010F3B8(q[0], func_0010F3A8(q[0]));
        q += 2;
    }
    D_001326B0[0] = func_0010F3A8(3);
}
