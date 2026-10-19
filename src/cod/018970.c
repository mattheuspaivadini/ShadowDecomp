/* asm/cod/018970.s -> sceInetRecv.
 * SCE libinet; receive counterpart of sceInetSend (018B48): request record, func_00118380 RPC, bounded copy-out via func_00118490 (Session 28).
 * MATCHED. */
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118490(int a0, int buf, int *p, int a3, int a4);

int sceInetRecv(int a0, int *p, int a2, int buf, int a4, int *q, int a6) {
    int r;

    p[0] = a2;
    if (q != 0)
        p[1] = q[0];
    else
        p[1] = 0;
    p[3] = a6;
    p[2] = a4;
    r = func_00118380(a0, 4, p, 0x10, a4 + 8);
    if (r < 0)
        return -0x21E;
    r = p[0];
    if (r < 0)
        return r;
    if (q != 0)
        q[0] = p[1];
    r = func_00118490(a0, buf, p, 2, p[0]);
    if (r < 0)
        return r;
    return p[0];
}
