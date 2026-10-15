/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=29].
 * R4 w25a_2: same with the extra or 0x8
 * The original .s stays in the build (asm/cod/014E68.s); this C
 * draft (Session 8) is kept for the record. */
struct S014E68 {
    unsigned int flags;    /* 0x00 */
    char pad04[0x0C];
    unsigned int field10;  /* 0x10 */
    char pad14[0x0C];
    int field20;           /* 0x20 */
};

unsigned int func_001148B8(unsigned int x);
int  func_001147C0(unsigned int *p);

void func_00114E68(struct S014E68 *p, unsigned int a1, int a2) {
    unsigned int r;

    r = func_001148B8(a1);
    func_001147C0(&p->flags);
    if (p->field10 != 0xFFFFFFFF)
        p->field10 = r;
    p->field20 = a2;
    p->flags &= ~0xC;
    p->flags |= 0x8;
    p->flags &= ~1;
    p->flags |= 0x100;
}
