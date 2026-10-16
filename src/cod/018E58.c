/* asm/cod/018E58.s -> func_00118438.
 * 018xxx family twin of 018D28 (op 9)
 * MATCHED (Session 8). */
int func_00118438(int a0, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118490(int a0, int a1, int *p, int a3, int a4);

int sceInetInterfaceControl(int a0, int *p, int a2, int a3, int a4, int a5) {
    int r;

    p[0] = a2;
    p[1] = a3;
    p[2] = a5;
    r = func_00118438(a0, (int)p, 3, a4, a5);
    if (r < 0)
        return r;
    r = func_00118380(a0, 9, p, a5 + 0xC, a5 + 0xC);
    if (r < 0)
        return -0x21E;
    r = func_00118490(a0, a4, p, 3, a5);
    if (r < 0)
        return r;
    return p[0];
}
