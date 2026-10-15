/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 40 [cc=296].
 * R2 w45a_0: rotated-loop (record counter + post-increment arg)
 * The original .s stays in the build (asm/cod/0016E8.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_00136100[];

void func_001000D0(int a0, int a1, int a2);
void func_001285C0(int a0, int a1);

struct Rec001016E8 {
    int  f0;        /* 0x00 */
    int  f4;        /* 0x04 */
    char pad[0x14];
};

struct Mod001016E8 {
    int  f0;        /* 0x00 */
    char pad04[0x4];
    int  f8;        /* 0x08 */
    char pad0C[0x2C];
    int  f38;       /* 0x38 */
    struct Rec001016E8 *f3C;    /* 0x3C */
};

int func_001016E8(struct Mod001016E8 *p) {
    struct Rec001016E8 *r;
    int n;
    int i;
    int c;

    if (p == 0)
        return 1;
    while (p != 0) {
        n = p->f38 - 1;
        r = p->f3C;
        for (; n != -1; n--) {
            if (r->f0 == 4 || r->f0 == 9) {
                c = r->f4;
                if (c > 0) {
                    i = 0;
                    while (i < c) {
                        i++;
                        func_001000D0((int)p, (int)r, i);
                    }
                }
            }
        }
        if (p->f8 != 0) {
            func_001285C0((int)D_00136100, (int)((char *)p + p->f8));
            p = (struct Mod001016E8 *)((char *)p + p->f8);
        } else {
            p = 0;
        }
    }
    return 1;
}
