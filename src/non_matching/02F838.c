/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 53 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02F838.s); this C
 * draft (Session 9) is kept for the record. */
struct N02F838 {
    char pad00[0x38];
    int  f38;
};

struct S02F838 {
    int            f00;
    int            f04;
    int            f08;
    unsigned short f0C;
    short          pad0E;
    int            f10;
    int            f14;
    int            f18;
    int            f1C;
    int            f20;
    char           pad24[0xC];
    int            f30;
    char           pad34[0x4];
    int            f38;
    int            f3C;
    char           pad40[0x14];
    struct N02F838 *f54;
};

extern int D_00135C60[];

int func_0012DA00(int node);
int func_0012D6D8(struct S02F838 *p);
int func_0012DBB0(int node, int buf);
int func_0012E578(struct S02F838 *p);
int func_0012E3F8(int node, void (*fn)(int));
void func_0012F800(int node);

int func_0012F838(struct S02F838 *p) {
    struct N02F838 *node;
    int b;
    int cb_arg;
    int r;
    unsigned short v;

    node = p->f54;
    if (node == 0) {
        node = (struct N02F838 *)D_00135C60[0];
        p->f54 = node;
    }
    if (node->f38 == 0)
        func_0012DA00((int)node);
    if (p->f0C & 0x20)
        return -1;
    p->f04 = 0;
    if (p->f0C & 0x4) {
        b = p->f30;
        if (b == 0)
            goto run;
        if (b != (int)((char *)p + 0x40))
            func_0012DBB0((int)node, b);
        p->f30 = 0;
        p->f04 = p->f3C;
        if (p->f3C == 0)
            goto run;
        p->f00 = p->f38;
        return 0;
    }
    if (!(p->f0C & 0x10))
        return -1;
    v = p->f0C;
    if (v & 8) {
        if (func_0012D6D8(p) != 0)
            return -1;
        v = p->f0C;
        p->f08 = 0;
        v &= 0xFFF7;
        p->f18 = 0;
        p->f0C = v;
    }
    p->f0C = v | 4;
run:
    if (p->f10 == 0)
        func_0012E578(p);
    if ((p->f0C & 3) != 0)
        func_0012E3F8((int)node, func_0012F800);
    cb_arg = p->f10;
    p->f00 = cb_arg;
    r = ((int (*)(int, int, int))p->f20)(p->f1C, cb_arg, p->f14);
    v = (unsigned short)(p->f0C & 0xDFFF);
    p->f04 = r;
    p->f0C = v;
    if (r > 0)
        return 0;
    if (r == 0) {
        p->f0C = v | 0x20;
    } else {
        p->f0C = v | 0x40;
        p->f04 = 0;
    }
    return -1;
}
