/* STATUS (10, 2026-10-16): NON_MATCHING. best score 4 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/02D850.s); this C
 * draft (10) is kept for the record. */
extern int _malloc_r(int a0, int a1);
extern void func_001283D0(void *dst, int value, int size);

int *__sfmoreglue(int a0, int n) {
    int size;
    int *p;
    int *b;

    size = n * 0x58;
    p = (int *)_malloc_r(a0, size + 0xC);
    b = (int *)((char *)p + 0xC);
    if (p != 0) {
        p[1] = n;
        p[0] = 0;
        p[2] = (int)b;
        func_001283D0(b, 0, size);
    }
    return p;
}
