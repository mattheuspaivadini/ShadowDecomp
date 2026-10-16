/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 18 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02D8C8.s); this C
 * draft (Session 9) is kept for the record. */
struct Ent02D8C8 {
    int   f00;              /* 0x00 */
    int   f04;              /* 0x04 */
    int   f08;              /* 0x08 */
    short f0C;              /* 0x0C */
    short f0E;              /* 0x0E */
    int   f10;              /* 0x10 */
    int   f14;              /* 0x14 */
    int   f18;              /* 0x18 */
    char  pad1C[0x14];
    int   f30;              /* 0x30 */
    int   f34;              /* 0x34 */
    char  pad38[0xC];
    int   f44;              /* 0x44 */
    int   f48;              /* 0x48 */
    char  pad4C[0x8];
    int   f54;              /* 0x54 */
};

struct Node02D8C8 {
    int next;               /* 0x00 */
    int count;              /* 0x04 */
    int ents;               /* 0x08 */
};

struct File02D8C8 {
    int   f00;              /* 0x00 */
    char  pad04[0x34];
    int   f38;              /* 0x38 */
    char  pad3C[0x18];
    int   f54;              /* 0x54 */
    char  pad58[0x180];
    struct Node02D8C8 node; /* 0x1D8 */
};

extern void __sinit(int a0);
extern int __sfmoreglue(int a0, int a1);

struct Ent02D8C8 *__sfp(struct File02D8C8 *p) {
    struct Node02D8C8 *n;
    struct Ent02D8C8 *e;
    int t;
    int i;

    if (p->f38 == 0)
        __sinit((int)p);
    n = &p->node;
    for (;;) {
        i = n->count - 1;
        e = (struct Ent02D8C8 *)n->ents;
        while (i >= 0) {
            if (e->f0C == 0)
                goto found;
            i--;
            e++;
        }
        t = n->next;
        if (t != 0) {
            n = (struct Node02D8C8 *)t;
            continue;
        }
        t = __sfmoreglue((int)p, 4);
        n->next = t;
        if (t == 0) {
            p->f00 = 0xC;
            return 0;
        }
        n = (struct Node02D8C8 *)t;
    }
found:
    e->f0E = -1;
    e->f54 = (int)p;
    e->f00 = 0;
    e->f08 = 0;
    e->f04 = 0;
    e->f10 = 0;
    e->f14 = 0;
    e->f18 = 0;
    e->f30 = 0;
    e->f34 = 0;
    e->f44 = 0;
    e->f48 = 0;
    e->f0C = 1;
    return e;
}
/* func_0012D8C8 */
