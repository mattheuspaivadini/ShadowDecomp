/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/0199F8.s); this C
 * draft (10) is kept for the record. */
int DIntr(void);
int EIntr(void);

int func_001199F8(int a0) {
    int count;
    char *p;
    int i;
    int idx;
    int n;

    DIntr();
    count = *(int *)(a0 + 8);
    p = *(char **)(a0 + 4);
    i = 0;
    if (count > 0) {
        do {
            if ((*(int *)(p + 0x10) & 1) == 0) {
                *(int *)(p + 0x10) = (i << 16) | 5;
                idx = *(int *)a0;
                n = idx + 1;
                *(int *)a0 = n;
                if (n == 1) {
                    *(int *)a0 = idx + 2;
                    n = 1;
                }
                *(int *)(p + 0x14) = (int)p;
                *(int *)(p + 0x18) = n;
                EIntr();
                return (int)p;
            }
            i++;
            p += 0x40;
        } while (i < count);
    }
    EIntr();
    return 0;
}
