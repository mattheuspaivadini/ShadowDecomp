/* asm/cod/018B48.s -> func_00118438.
 * 018xxx family (7-arg variant of the 019210 q-block shape)
 * MATCHED (Session 8). */
int func_00118438(int a0, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int *p, int a3, int a4);

int func_00118B48(int a0, int *p, int a2, int a3, int a4, int *q, int a6) {
    int r;

    p[0] = a2;
    if (q != 0)
        p[1] = q[0];
    else
        p[1] = 0;
    p[2] = a4;
    p[3] = a6;
    r = func_00118438(a0, (int)p, 4, a3, a4);
    if (r < 0)
        return r;
    r = func_00118380(a0, 5, p, a4 + 0x10, 8);
    if (r < 0)
        return -0x21E;
    if (q != 0)
        q[0] = p[1];
    return p[0];
}
