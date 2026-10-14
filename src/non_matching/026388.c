/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * 16 instructions: list-walk loop rotation.
 * See docs/progress.md for the family classification. */
/* func_00126388 @ 0x00126388 (0x58 bytes): variable-stride list walk; return
 * the first node whose (t - f8) < fC (f4 and f8 both set), else 0. */
struct N026388 {
    int size;   /* 0x0 */
    int f4;     /* 0x4 */
    int f8;     /* 0x8 */
    int fC;     /* 0xC */
};

struct N026388 *func_00126388(struct N026388 *p, int t) {
    int n = p->size;

    while (n != 0) {
        if (p->f4 != 0 && p->f8 != 0
            && (unsigned)(t - p->f8) < (unsigned)p->fC)
            return p;
        p = (struct N026388 *)((char *)p + n + 4);
        n = p->size;
    }
    return 0;
}
