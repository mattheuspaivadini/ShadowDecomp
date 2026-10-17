/* asm/cod/019568.s -> func_00119568.
 * SCE libnet interface scan; early -2 return after the loop (Session 19)
 * MATCHED. */
int sceInetGetInterfaceList(int a0, int a1, int a2, int a3);
int sceInetInterfaceControl(int a0, int a1, int a2, int a3, int a4, int a5);

int func_00119568(int a0, int a1, int *out) {
    int buf[0x100];
    int v;
    int n;
    int i;

    n = sceInetGetInterfaceList(a0, a1, (int)buf, 0x100);
    if (n < 0)
        return -1;
    if (n == 0)
        return -2;
    for (i = 0; i < n; i++) {
        if (sceInetInterfaceControl(a0, a1, buf[i], 8, (int)&v, 4) < 0)
            return -1;
        if (v & 2)
            break;
    }
    if (i == n)
        return -2;
    *out = buf[i];
    return 0;
}
