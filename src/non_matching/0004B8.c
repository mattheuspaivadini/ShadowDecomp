/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 13 [cc=296].
 * R2 w45a_0: scheduling (load hoisting above the store block)
 * The original .s stays in the build (asm/cod/0004B8.s); this C
 * draft (Session 8) is kept for the record. */
void func_001004B8(char *p) {
    int n;
    int cnt;
    char *q;
    char *t;

    n = *(int *)(p + 0x40);
    t = p + *(int *)(p + 0x5C);
    *(int *)(p + 0x30) = (int)t;
    if (n > 0) {
        q = t;
        cnt = n;
        do {
            *(int *)(q + 0x04) = (int)(p + *(int *)(q + 0x1C));
            q += 0x20;
        } while (--cnt);
    }
    *(int *)(p + 0x28) = (int)(p + *(int *)(p + 0x54));
    *(int *)(p + 0x34) = (int)(p + *(int *)(p + 0x60));
    *(int *)(p + 0x2C) = (int)(p + *(int *)(p + 0x58));
    *(int *)(p + 0x20) = (int)(p + *(int *)(p + 0x50));
    *(int *)(p + 0x48) = (int)(p + *(int *)(p + 0x6C));
    *(int *)(p + 0x44) = (int)(p + *(int *)(p + 0x68));
    *(int *)(p + 0x3C) = (int)(p + *(int *)(p + 0x64));
    n = *(int *)(p + 0x38);
    if (n > 0) {
        q = p + *(int *)(p + 0x64);
        cnt = n;
        do {
            *(int *)(q + 0x0C) = (int)(p + *(int *)(q + 0x14));
            *(int *)(q + 0x10) = (int)(p + *(int *)(q + 0x18));
            q += 0x1C;
        } while (--cnt);
    }
    *(int *)(p + 0x18) = (int)(p + *(int *)(p + 0x14));
}
