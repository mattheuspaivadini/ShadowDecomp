/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 29 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02D6D8.s); this C
 * draft (Session 9) is kept for the record. */
struct File02D6D8 {
    int   f00;              /* 0x00 */
    int   f04;              /* 0x04 */
    int   f08;              /* 0x08 */
    short f0C;              /* 0x0C */
    short f0E;              /* 0x0E */
    int   f10;              /* 0x10 */
    int   f14;              /* 0x14 */
    int   f18;              /* 0x18 */
    int   f1C;              /* 0x1C */
    int   f20;              /* 0x20 */
    int   f24;              /* 0x24 */
    int   f28;              /* 0x28 */
    int   f2C;              /* 0x2C */
    int   f30;              /* 0x30 */
    int   f34;              /* 0x34 */
    int   f38;              /* 0x38 */
    char  pad3C[0x18];
    int   f54;              /* 0x54 */
};

extern int D_00135C60[];    /* .data 0x00135C60: the default stream */
extern void func_0012DA00(int a0);
extern int func_0012E3F8(int a0, int a1);

int func_0012D6D8(struct File02D6D8 *p) {
    struct File02D6D8 *f;
    int ofs;
    int n;
    int ret;
    int r;

    if (p == 0)
        return func_0012E3F8(D_00135C60[0], (int)func_0012D6D8);
    f = (struct File02D6D8 *)p->f54;
    if (f == 0) {
        f = (struct File02D6D8 *)D_00135C60[0];
        p->f54 = (int)f;
    }
    if (f->f38 == 0)
        func_0012DA00((int)f);
    if ((p->f0C & 8) == 0)
        return 0;
    n = p->f10;
    if (n == 0)
        return 0;
    ofs = 0;
    ret = p->f00 - n;
    p->f00 = n;
    if ((p->f0C & 3) == 0)
        ofs = p->f14;
    p->f08 = ofs;
    if (ret <= 0)
        return 0;
    while (ret > 0) {
        r = (*(int (*)(int, int, int))p->f24)(p->f1C, n, ret);
        if (r <= 0) {
            p->f0C = p->f0C | 0x40;
            return -1;
        }
        ret = ret - r;
        n = n + r;
    }
    return 0;
}
