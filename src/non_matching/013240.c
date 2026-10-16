/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 20 [cc=29].
 * R4 w25a_2: movn if-conversion + byte-vs-element diff
 * The original .s stays in the build (asm/cod/013240.s); this C
 * draft (Session 8) is kept for the record. */
struct S013240 {
    unsigned int *write;   /* 0x00 */
    char pad04[0x10];
    unsigned int *last;    /* 0x14 */
};

void sceVif1PkCloseGifTag(struct S013240 *p) {
    unsigned int *last;
    unsigned int *write;
    unsigned long long v;
    unsigned int n;
    int t;
    unsigned int sz;

    last = p->last;
    write = p->write;
    v = *(unsigned long long *)last;
    n = (unsigned int)(((int)write - (int)last) >> 3) - 2;
    t = (int)((v >> 58) & 3);
    if (t != 1)
        n = n >> 1;
    if (t != 2) {
        sz = (unsigned int)(v >> 60);
        if (sz == 0)
            sz = 16;
        n = (n + sz - 1) / sz;
    }
    p->last = 0;
    *(unsigned long long *)last = v + (unsigned int)n;
    if (((unsigned int)write & 0xC) != 0) {
        do {
            *write = 0;
            write = write + 1;
        } while (((unsigned int)write & 0xC) != 0);
    }
    p->write = write;
}
/* func_00113240 */
