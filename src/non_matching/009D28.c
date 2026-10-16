/* STATUS (10, 2026-10-16): NON_MATCHING. best score 7 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/009D28.s); this C
 * draft (10) is kept for the record. */
int func_0010FB20(void);
int func_0010FB70(void);

int sceSifRemoveRpc(int a0, int *a1) {
    int *p;

    func_0010FB20();
    p = (int *)a1[0x08 / 4];
    if (p == (int *)a0) {
        a1[0x08 / 4] = p[0x38 / 4];
    } else if (p != 0) {
        while (p != 0 && p[0x38 / 4] != a0)
            p = (int *)p[0x38 / 4];
        if (p != 0)
            p[0x38 / 4] = ((int *)a0)[0x38 / 4];
    }
    func_0010FB70();
    return (int)p;
}
