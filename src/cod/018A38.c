/* asm/cod/018A38.s -> sceInetRecvFrom.
 * SCE libinet; sceInetRecv plus the source-address copy-out (9th argument on the stack) (Session 28).
 * MATCHED. */
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118490(int a0, int buf, int *p, int a3, int a4);

int sceInetRecvFrom(int a0, int *p, int a2, int buf, int a4, int *q, int addr, int *paddrlen, int a8) {
    int r;

    p[0] = a2;
    if (q != 0)
        p[1] = q[0];
    else
        p[1] = 0;
    p[2] = a4;
    p[3] = a8;
    r = func_00118380(a0, 0xD, p, 0x10, a4 + 0x1C);
    if (r < 0)
        return -0x21E;
    r = p[0];
    if (r < 0)
        return r;
    if (q != 0)
        q[0] = p[1];
    r = func_00118490(a0, addr, p, 2, 0x10);
    if (r < 0)
        return r;
    if (paddrlen != 0)
        *paddrlen = p[6];
    r = func_00118490(a0, buf, p, 7, p[0]);
    if (r < 0)
        return r;
    return p[0];
}
