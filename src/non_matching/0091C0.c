/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 18 [cc=29].
 * R4 w25a_0: k++/if(k==1) store pair
 * The original .s stays in the build (asm/cod/0091C0.s); this C
 * draft (Session 8) is kept for the record. */
struct S0091C0 {
    int    f0;      /* 0x0 */
    char  *arr;     /* 0x4 */
    int    n;       /* 0x8 */
};

void DIntr(void);
void EIntr(void);

void *func_001091C0(struct S0091C0 *s) {
    int   i;
    int   n;
    int   k;
    char *p;

    DIntr();
    n = s->n;
    i = 0;
    if (n <= 0)
        goto fail;
    p = s->arr;
    for (; i < n; i++) {
        if ((*(int *)(p + 0x10) & 1) == 0) {
            *(int *)(p + 0x10) = (i << 16) | 5;
            k = s->f0;
            k++;
            s->f0 = k;
            if (k == 1) {
                s->f0 = k + 1;
                i = 1;
            }
            *(int *)(p + 0x14) = (int)p;
            *(int *)(p + 0x18) = i;
            EIntr();
            return p;
        }
        p += 0x40;
    }
fail:
    EIntr();
    return 0;
}
