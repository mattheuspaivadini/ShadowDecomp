/* asm/cod/018870.s -> func_00118438.
 * session9 step1 residue: held 2nd call result
 * MATCHED (Session 8). */
int func_00118438(int a0, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int *p, int a3, int a4);

int sceInetCreate(int a0, int a1, int a2) {
    int r;
    int w;

    r = func_00118438(a0, a1, 1, a2, 0x40);
    if (r < 0)
        return r;
    r = func_00118380(a0, 1, (int *)a1, 0x44, 4);
    if (r < 0)
        return -0x21E;
    w = *(int *)a1;
    return w ? w : -0x21C;
}
