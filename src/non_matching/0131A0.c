/* STATUS (Session 8, 2026-10-16): NON_MATCHING. best score 8 [cc=29].
 * reg-alloc of q in a1 vs a0 across movn
 * The original .s stays in the build (asm/cod/0131A0.s); this C
 * draft (Session 8) is kept for the record. */
struct S0131A0 {
    int *field00;
    int  field04;
    int  field08;
    int *field0C;
};

void sceVif1PkAlign(struct S0131A0 *p, int a1, int a2);

void sceVif1PkOpenDirectCode(struct S0131A0 *p, int flag) {
    int *q;
    int v;

    sceVif1PkAlign(p, 2, 3);
    v = 0x50000000;
    if (flag)
        v = 0xD0000000;
    q = p->field00;
    p->field00 = q + 1;
    p->field0C = q;
    *q = v;
}
