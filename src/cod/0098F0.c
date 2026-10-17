/* asm/cod/0098F0.s -> func_001098F0.
 * copy-order: explicit temporaries group the two loads; TU built with -fno-strict-aliasing (Session 20)
 * MATCHED. */
/* asm/cod/0098F0.s -> func_001098F0 @ 0x001098F0 (0x8C bytes, 35 insns)
 *
 * Leaf helper over the object table D_00145940 (list head at +0x28; the nodes'
 * forward link is at +0x14). It links node a1 into a2, copies eight fields from
 * a0 into a1 and then, if the a2 object carries no pending condition, hands
 * off to func_00107858 with a2->f00 as the argument:
 *
 *   a1 = a0->f34;  a2 = a1->f40;
 *   if (a2->f0C == 0) a2->f0C = a1;        ; bnel ... + sw in the `b` slot
 *   else              a2->f10->f3C = a1;
 *   a2->f10 = a1;
 *   a1->f20 = a0->f14;  a1->f1C = a0->f1C; a1->f24 = a0->f20;
 *   a1->f0C = a0->f24;  a1->f28 = a0->f28; a1->f2C = a0->f2C;
 *   a1->f30 = a0->f30;  a1->f34 = a0->f10;
 *   if (a2->f00 >= 0 && a2->f04 == 0)
 *       func_00107858(a2->f00);            ; `j` sibling call, $a0 = a2->f00
 *
 * The eight copies are in the asm's statement order; the `j func_00107858`
 * has a `nop` delay slot and is the only call (both routines are void), so it
 * is a void tail call. UNCONFIRMED: struct/field semantics (only the offsets
 * and the 32-bit widths are evidenced).
 * MATCH GUESS: cc=29 (the 0x00109xxx block is a 2.9 TU range; the void tail
 * call is the documented 2.9-frame `j` shape) */
struct S98N {
    int          f00;   /* 0x00 */
    int          f04;   /* 0x04 */
    char         pad08[4];
    void        *f0C;   /* 0x0C */
    struct S98N *f10;   /* 0x10 */
    char         pad14[8];
    void        *f1C;   /* 0x1C */
    void        *f20;   /* 0x20 */
    void        *f24;   /* 0x24 */
    void        *f28;   /* 0x28 */
    void        *f2C;   /* 0x2C */
    void        *f30;   /* 0x30 */
    struct S98N *f34;   /* 0x34 */
    char         pad38[4];
    void        *f3C;   /* 0x3C */
    struct S98N *f40;   /* 0x40 */
};

struct S98A {
    char         pad00[0x10];
    void        *f10;   /* 0x10 */
    void        *f14;   /* 0x14 */
    char         pad18[4];
    void        *f1C;   /* 0x1C */
    void        *f20;   /* 0x20 */
    void        *f24;   /* 0x24 */
    void        *f28;   /* 0x28 */
    void        *f2C;   /* 0x2C */
    void        *f30;   /* 0x30 */
    struct S98N *f34;   /* 0x34 */
};

void iWakeupThread(int code);

void func_001098F0(struct S98A *a0) {
    struct S98N *a1;
    struct S98N *a2;

    a1 = a0->f34;
    a2 = a1->f40;
    if (a2->f0C == 0)
        a2->f0C = a1;
    else
        a2->f10->f3C = a1;
    a2->f10 = a1;
    {
        void *t1 = a0->f14;
        void *t2 = a0->f1C;
        a1->f20 = t1;
        a1->f1C = t2;
    }
    a1->f24 = a0->f20;
    a1->f0C = a0->f24;
    a1->f28 = a0->f28;
    a1->f2C = a0->f2C;
    a1->f30 = a0->f30;
    a1->f34 = a0->f10;
    if (a2->f00 >= 0 && a2->f04 == 0)
        iWakeupThread(a2->f00);
}
