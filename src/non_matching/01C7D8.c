/* STATUS (10, 2026-10-16): NON_MATCHING. best score 7 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/01C7D8.s); this C
 * draft (10) is kept for the record. */
extern char gSceMc2SysInfo[];   /* 0x184-stride records (lui/%lo) */
extern char D_0015DF48[];   /* 0x898-stride records (lui/%lo) */

int func_0011C3B0(int index, int slot, int *out);

int func_0011C7D8(int index, int *out) {
    char *base;
    char *p;
    int i;
    int n;
    int r;

    base = gSceMc2SysInfo + index * 0x184;
    p = D_0015DF48 + index * 0x898;
    *out = 0;
    i = *(int *)(p + 0x890);
    n = 0;
    while (i < *(int *)(base + 0x170)) {
        r = func_0011C3B0(index, i, out);
        if (*out != 0)
            return 0;
        if ((r & 0x80000000) == 0)
            n = n + 1;
        i = i + 1;
    }
    return n;
}
