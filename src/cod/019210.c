/* asm/cod/019210.s -> func_00118380.
 * beql answer copy-back; wave3e (R1)
 * MATCHED (Session 8). */
int func_00118380(int a0, int a1, int *a2, int a3, int a4);

int func_00119210(int a0, int *p, int v, int *q) {
    p[0] = v;
    if (q != 0)
        p[1] = q[0];
    else
        p[1] = 0;
    if (func_00118380(a0, 0x35, p, 8, 8) < 0)
        return -0x21E;
    if (q != 0)
        q[0] = p[1];
    return p[0];
}
