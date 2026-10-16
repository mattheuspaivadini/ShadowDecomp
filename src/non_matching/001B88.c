/* STATUS (Session 8, 2026-10-16): NON_MATCHING. best score 9 [cc=296].
 * thread-init handler scheduling
 * The original .s stays in the build (asm/cod/001B88.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00139E04;
extern char D_00136400[];

int func_0012821C(int a0, int a1, int a2);
void func_00102CF8(int a0, int a1, int a2, int a3, int a4, int a5);

struct Rec00101B88 {
    int f0;         /* 0x00 */
    int f4;         /* 0x04 */
    int f8;         /* 0x08 */
    int fC;         /* 0x0C */
    int f10;        /* 0x10 */
    int f14;        /* 0x14 */
    int f18;        /* 0x18 */
};

struct Hdr00101B88 {
    char pad00[0x38];
    int  f38;       /* 0x38 */
    char *f3C;      /* 0x3C */
};

int func_00101B88(int a0, int a1, int *a2) {
    struct Hdr00101B88 *v0;
    struct Rec00101B88 *dst;
    struct Rec00101B88 *p;
    int n;
    int i;
    int s0;
    int s1;

    v0 = (struct Hdr00101B88 *)a2[0];
    dst = (struct Rec00101B88 *)a2[2];
    n = v0->f38 >> 1;
    s1 = a2[3];
    p = (struct Rec00101B88 *)(v0->f3C + n * 0x1C);
    for (i = n; i != 0; i--) {
        s0 = p->f4;
        *dst = *p;
        func_0012821C(s1, p->fC, s0 * 8);
        dst->fC = s1;
        s1 += s0 * 8;
        func_0012821C(s1, p->f10, s0 * 8);
        dst->f10 = s1;
        s1 += s0 * 8;
        p++;
        dst++;
    }
    func_00102CF8((int)D_00136400, a1, a2[2], (int)dst, a2[3], s1);
    a2[1] = n;
    D_00139E04 = a1;
    return 0;
}
