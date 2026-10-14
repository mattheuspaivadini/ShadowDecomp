/* asm/cod/018710.s -> func_00118438.
 * first guard returns callee code; wave4c (R1)
 * MATCHED (Session 8). */
int func_00118438(int a0, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int a2, int a3, int a4);
int func_00118578(int a0, int a1, int a2);

int func_00118710(int a0, int *a1, int a2, int a3, int a4) {
    int r;

    a1[0] = a3;
    r = func_00118438(a0, (int)a1, 1, a4, 0x10);
    if (r < 0)
        return r;
    r = func_00118380(a0, 7, (int)a1, 0x14, a3 + 0x14);
    if (r < 0)
        return -0x21E;
    r = func_00118578(a2, (int)a1, 5);
    if (r >= 0)
        return a1[0];
    return r;
}
