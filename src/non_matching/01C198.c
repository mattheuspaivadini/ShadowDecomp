/* STATUS (Session 4, 2026-10-14): NON_MATCHING. same record-init family as func_0011C138.
 * The original .s stays in the build (asm/cod/01C198.s); this C
 * attempt is kept for the record. */
/* asm/cod/01C198.s -> func_0011C198 @ 0x0011C198 (0x68 bytes)
 *   addiu $v0, $zero, 0x898
 *   mult  $a0, $a0, $v0                ; index * 0x898
 *   ... record = D_0015DF48 + index*0x898 ...
 *   sw    -1  at +0x800, +0x804
 *   sw     0  at +0x894
 *   sw     1  at +0x888
 *   sw     0  at +0x88C, +0x890
 *   sb    D_00138D08[0], D_00138D08[1] at +0x808
 *   jr    $ra
 *    addiu $v0, $zero, 0x1
 *
 * Initialise one 0x898-byte record: two -1 sentinels, a 1/0/0 triple and a
 * two-byte copy from D_00138D08. Sibling of func_0011C138 (which loops twice).
 */
struct R01C198 {
    char pad00[0x800];
    int  field800;      /* 0x800 */
    int  field804;      /* 0x804 */
    char field808[0x80];/* 0x808 */
    int  field888;      /* 0x888 */
    int  field88C;      /* 0x88C */
    int  field890;      /* 0x890 */
    int  field894;      /* 0x894 */
};

extern struct R01C198 D_0015DF48[];
extern char D_00138D08[];

int _sceMcFatInit2(int index) {
    struct R01C198 *p = &D_0015DF48[index];

    p->field800 = -1;
    p->field804 = -1;
    p->field894 = 0;
    p->field888 = 1;
    p->field88C = 0;
    p->field890 = 0;
    p->field808[0] = D_00138D08[0];
    p->field808[1] = D_00138D08[1];
    return 1;
}
