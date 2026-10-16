/* STATUS (10, 2026-10-16): NON_MATCHING. best score 6 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/019568.s); this C
 * draft (10) is kept for the record. */
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
    if (i != n) {
        *out = buf[i];
        return 0;
    }
    return -2;
}
