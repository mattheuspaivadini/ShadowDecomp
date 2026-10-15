/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 55 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/025A38.s); this C
 * draft (Session 9) is kept for the record. */
struct L25A38 {
    void **ptr;     /* 0x00 */
    int     count;  /* 0x04 */
};

struct E25A38 {
    int w0;     /* 0x00 */
    int w4;     /* 0x04 */
    int key;    /* 0x08 */
};

void func_00125A38(struct L25A38 *a, struct L25A38 *b) {
    int   n;
    int   i;
    void **A;
    void **B;

    n = a->count;
    i = b->count;
    A = a->ptr;
    B = b->ptr;
    if (i == 0)
        return;
    do {
        void *e;

        i--;
        e = B[i];
        while (n != 0
               && ((struct E25A38 *)A[n - 1])->key > ((struct E25A38 *)e)->key) {
            A[n + i] = A[n - 1];
            n--;
        }
        A[n + i] = e;
    } while (i != 0);
    a->count = a->count + b->count;
}
