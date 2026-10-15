/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 33 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/019C08.s); this C
 * draft (Session 9) is kept for the record. */
struct SemaParam_019C08 {
    int f00;    /* 0x00 */
    int f04;    /* 0x04 */
    int f08;    /* 0x08 */
    int f0C;    /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14  name pointer */
};

struct N019C08 {
    char pad00[0x14];
    int  f14;   /* 0x14 self */
    int  f18;   /* 0x18 slot index */
    int  f1C;   /* 0x1C owner */
    int  f20;   /* 0x20 */
    int  f24;   /* 0x24 */
    int  f28;   /* 0x28 */
    int  f2C;   /* 0x2C */
};

struct C019C08 {
    int f00;    /* 0x00 node */
    int f04;    /* 0x04 node slot index */
    int f08;    /* 0x08 sema "SceMrpcBind1" */
    int f0C;    /* 0x0C */
    int f10;    /* 0x10 a1 */
    int f14;    /* 0x14 */
    int f18;    /* 0x18 */
    int f1C;    /* 0x1C */
    int f20;    /* 0x20 */
    int f24;    /* 0x24 done flag */
    int f28;    /* 0x28 sema "SceMrpcBind0" */
    int f2C;    /* 0x2C */
    int f30;    /* 0x30 a3 */
    int f34;    /* 0x34 a4 */
    int f38;    /* 0x38 a5 */
};

extern char D_00138B28[];
extern char D_00138B50[];
extern char D_00138B60[];
extern int D_001518C0[];

int func_00108EF8(const char *msg);
int func_00106FE0(void *param);
int func_00106FF0(int sema);
int func_00107020(int sema);
int func_001199F8(int pool);
void func_00119AA0(void *node);
int func_00112E00(int a0, int a1, int a2, int a3, int a4, int a5);

int SceMrpcBind(int a0, int a1, int a2, int a3, int a4, int a5) {
    struct C019C08 *c;
    struct N019C08 *n;
    struct SemaParam_019C08 buf;
    int r;

    c = (struct C019C08 *)a0;
    if (a2 != 0) {
        func_00108EF8(D_00138B28);
        return -1;
    }
    buf.f08 = 1;
    buf.f14 = (int)D_00138B50;
    buf.f04 = 1;
    c->f28 = func_00106FE0(&buf);
    if (c->f28 < 0)
        return -3;
    func_00107020(c->f28);
    c->f10 = a1;
    c->f24 = 0;
    c->f30 = a3;
    c->f34 = a4;
    c->f38 = a5;
    n = (struct N019C08 *)func_001199F8((int)D_001518C0);
    if (n == 0) {
        func_00106FF0(c->f28);
        return -1;
    }
    c->f00 = (int)n;
    c->f04 = n->f18;
    n->f20 = a1;
    n->f24 = a3;
    n->f28 = a4;
    n->f2C = a5;
    n->f14 = (int)n;
    n->f1C = (int)c;
    buf.f04 = 1;
    buf.f14 = (int)D_00138B60;
    buf.f08 = 0;
    c->f08 = func_00106FE0(&buf);
    if (c->f08 < 0) {
        func_00119AA0(n);
        func_00106FF0(c->f28);
        return -3;
    }
    r = func_00112E00(0x80000019, (int)n, 0x40, 0, 0, 0);
    if (r == 0) {
        func_00119AA0(n);
        func_00106FF0(c->f08);
        func_00106FF0(c->f28);
        return -2;
    }
    func_00107020(c->f08);
    func_00106FF0(c->f08);
    if (c->f24 == 0)
        func_00106FF0(c->f28);
    return 0;
}
