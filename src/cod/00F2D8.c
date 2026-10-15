/* asm/cod/00F2D8.s -> func_00106C90.
 * R4 w25a_1
 * MATCHED (Session 8). */
void func_00106C90(unsigned int a0, int *a1);
void func_00106CA0(unsigned int a0, int *a1);

extern int D_00132670[];
extern int D_0010FA00[];

unsigned int func_0010F2D8(unsigned int idx, int val) {
    unsigned int i;
    int old;

    i = idx - 1;
    if (i >= 0xD)
        return 0xFFFFFFFFu;
    old = D_00132670[idx];
    D_00132670[idx] = val;
    if (i < 3)
        func_00106C90(idx, D_0010FA00);
    else
        func_00106CA0(idx, D_0010FA00);
    return old;
}
