/* asm/cod/018F00.s -> func_00118380.
 * 018xxx family (cc=29 3-operand mult for the 0x48 stride)
 * MATCHED (Session 8). */
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118490(int a0, int a1, int *p, int a3, int a4);

int sceInetGetRoutingTable(int a0, int *p, int a2, int a3) {
    int r;

    p[0] = a3;
    r = func_00118380(a0, 0xA, p, 4, (a3 * 0x48) | 4);
    if (r < 0)
        return -0x21E;
    if (p[0] < 0)
        return p[0];
    r = func_00118490(a0, a2, p, 1, p[0] * 0x48);
    if (r < 0)
        return r;
    return p[0];
}
