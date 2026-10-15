/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 6 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/019568.s); this C
 * draft (Session 9) is kept for the record. */
int func_00118DD0(int a0, int a1, int a2, int a3);
int func_00118E58(int a0, int a1, int a2, int a3, int a4, int a5);

int func_00119568(int a0, int a1, int *out) {
    int buf[0x100];
    int v;
    int n;
    int i;

    n = func_00118DD0(a0, a1, (int)buf, 0x100);
    if (n < 0)
        return -1;
    if (n == 0)
        return -2;
    for (i = 0; i < n; i++) {
        if (func_00118E58(a0, a1, buf[i], 8, (int)&v, 4) < 0)
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
