/* asm/cod/0199F8.s -> func_001199F8.
 * free-slot scan + id counter skipping 0; explicit else arm keeps the n=1 rematerialisation (Session 19)
 * MATCHED. */
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
                *(int *)a0 = idx + 1;
                if (idx + 1 == 1) {
                    *(int *)a0 = idx + 2;
                    n = 1;
                } else
                    n = idx + 1;
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
