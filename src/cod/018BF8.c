/* asm/cod/018BF8.s -> sceInetSendTo.
 * SCE libinet; sceInetSend with the destination address staged through func_00118438 (9th argument on the stack) (Session 28).
 * MATCHED. */
int func_00118438(int a0, int a1, int a2, int a3, int a4);
int func_00118380(int a0, int a1, int *p, int a3, int a4);

int sceInetSendTo(int a0, int *p, int a2, int buf, int len, int *q, int addr, int a7, int a8) {
    int r;

    p[0] = a2;
    if (q != 0)
        p[1] = q[0];
    else
        p[1] = 0;
    p[2] = len;
    p[3] = a8;
    p[4] = a7;
    r = func_00118438(a0, (int)p, 5, addr, 0x10);
    if (r < 0)
        return r;
    r = func_00118438(a0, (int)p, 9, buf, len);
    if (r < 0)
        return r;
    r = func_00118380(a0, 0xE, p, len + 0x24, 8);
    if (r < 0)
        return -0x21E;
    if (q != 0)
        q[0] = p[1];
    return p[0];
}
