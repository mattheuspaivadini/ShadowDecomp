/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 36 [cc=296].
 * R2 w45a_0: loop condition re-read of p->f40
 * The original .s stays in the build (asm/cod/001800.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_00136100[];

void func_001285C0(int a0, int a1);

struct Rec00101800 {
    int  f0;        /* 0x00 */
    char pad04[0x14];
    int  f18;       /* 0x18 */
};

struct Mod00101800 {
    char pad00[0x08];
    int  f8;        /* 0x08 */
    char pad0C[0x24];
    struct Rec00101800 *f30;    /* 0x30 */
    char pad34[0x0C];
    int  f40;       /* 0x40 */
};

int FreeDecodedSection(struct Mod00101800 *p, void (*cb)(int)) {
    struct Rec00101800 *e;
    int i;

    if (p == 0)
        return 1;
    while (p != 0) {
        for (i = 1; i < p->f40; i++) {
            e = &p->f30[i];
            if (e->f18 != 0) {
                e->f18 = 0;
                cb(e->f0);
            }
        }
        if (p->f8 != 0) {
            func_001285C0((int)D_00136100, (int)((char *)p + p->f8));
            p = (struct Mod00101800 *)((char *)p + p->f8);
        } else {
            p = 0;
        }
    }
    return 1;
}
