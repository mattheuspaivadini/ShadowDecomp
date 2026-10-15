/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=29].
 * compile error first (inline-asm $gp); re-drafted as C, score 21
 * The original .s stays in the build (asm/cod/012C00.s); this C
 * draft (Session 8) is kept for the record. */
struct R012C00 {
    int f0;             /* 0x00 */
    int f4;             /* 0x04 */
    int f8;             /* 0x08 */
};

struct T012C00 {
    char             pad00[0xC];
    struct R012C00  *lo;        /* 0x0C */
    char             pad10[0x4];
    struct R012C00  *hi;        /* 0x14 */
};

extern struct T012C00 D_0014B358;   /* non-small: lui/%lo */

void func_00112C00(int id, int handler, int arg) {
    int             idx;
    int             g;
    struct R012C00 *rec;

    if (id < 0) {
        idx = id & 0x7FFFFFFF;
        rec = D_0014B358.lo + idx;
        rec->f4 = arg;
        rec->f0 = handler;
        __asm__ __volatile__("daddu %0,$gp,$zero" : "=r"(g));
        D_0014B358.lo[idx].f8 = g;
    } else {
        idx = id;
        rec = D_0014B358.hi + idx;
        rec->f4 = arg;
        rec->f0 = handler;
        __asm__ __volatile__("daddu %0,$gp,$zero" : "=r"(g));
        D_0014B358.hi[idx].f8 = g;
    }
}
