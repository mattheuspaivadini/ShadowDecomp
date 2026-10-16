/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 26 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02C0F8.s); this C
 * draft (Session 9) is kept for the record. */
struct S12C0F8 {
    int            f00;    /* 0x00 */
    int            f04;    /* 0x04 */
    int            f08;    /* 0x08 */
    unsigned short f0C;    /* 0x0C flags */
    char           pad0E[2];
    int            f10;    /* 0x10 buffer */
    int            f14;    /* 0x14 */
    int            f18;    /* 0x18 */
    char           pad1C[0x14];
    int            f30;    /* 0x30 */
    char           pad34[0xC];
    int            f40;    /* 0x40 internal buffer */
    char           pad44[0x10];
    int            f54;    /* 0x54 state object */
};

struct S12C0F8_P {         /* the object at s->f54 */
    char pad00[0x38];
    int  f38;              /* 0x38 */
};

extern int _impure_ptr[];

void __sinit(int a0);
void _free_r(int a0);
int  __smakebuf(int a0);

int __swsetup(struct S12C0F8 *s) {
    struct S12C0F8_P *p;
    int x;
    int b;
    int v;

    p = (struct S12C0F8_P *)s->f54;
    if (p == 0) {
        p = (struct S12C0F8_P *)_impure_ptr[0];
        s->f54 = (int)p;
    }
    if (p->f38 == 0)
        __sinit((int)p);
    x = s->f0C;
    if ((x & 8) == 0) {
        if ((x & 0x10) == 0)
            return -1;
        if ((x & 4) != 0) {
            b = s->f30;
            if (b != 0) {
                if (b != (int)&s->f40) {
                    _free_r(s->f54);
                    x = s->f0C;
                }
                s->f30 = 0;
            }
            x &= ~0x24;
            s->f04 = 0;
            s->f0C = x;
            s->f00 = s->f10;
        }
        s->f0C = x | 8;
    }
    if (s->f10 == 0) {
        __smakebuf((int)s);
        x = s->f0C;
    } else {
        x = s->f0C;
    }
    if (x & 1) {
        s->f08 = 0;
        s->f18 = -s->f14;
    } else {
        v = (x & 2) ? 0 : s->f14;
        s->f08 = v;
    }
    return 0;
}
/* func_0012C0F8 */
