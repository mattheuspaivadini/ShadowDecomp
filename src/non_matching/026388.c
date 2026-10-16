/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 10 [cc=296].
 * func_00126388: list-walk loop rotation and addu v0, a0, a3 delay slot
 * The original .s stays in the build (asm/cod/026388.s); this C
 * draft (Session 12) is kept for the record. */
struct N026388 {
    int size;   /* 0x0 */
    int f4;     /* 0x4 */
    int f8;     /* 0x8 */
    int fC;     /* 0xC */
};

struct N026388 *func_00126388(struct N026388 *p, int t) {
    int size = p->size;
    while (size != 0) {
        if (p->f4 != 0) {
            int f8 = p->f8;
            if (f8 != 0 && (unsigned int)(t - f8) < (unsigned int)p->fC)
                return p;
        }
        p = (struct N026388 *)((char *)p + size + 4);
        size = p->size;
    }
    return 0;
}
