/* asm/cod/01C138.s -> func_0011C138 @ 0x0011C138 (0x60 bytes)
 *   lui   $v0, %hi(D_0015DF48)
 *   addiu $a0, $zero, -0x1
 *   addiu $v0, $v0, %lo(D_0015DF48)    ; base
 *   addiu $a2, $zero, 0x1
 *   addiu $v0, $v0, 0x808              ; p = &base[0].field808
 *   lui   $a1, %hi(D_00138D08)
 *   addiu $v1, $zero, 0x1              ; i = 1
 * .L0011C158:
 *   sw    $a0, -0x8($v0)               ; field800 = -1
 *   addiu $v1, $v1, -0x1
 *   sw    $a0, -0x4($v0)               ; field804 = -1
 *   sw    $zero, 0x8C($v0)             ; field894 = 0
 *   sw    $a2, 0x80($v0)               ; field888 = 1
 *   sw    $zero, 0x84($v0)             ; field88C = 0
 *   sw    $zero, 0x88($v0)             ; field890 = 0
 *   ... two-byte copy D_00138D08 -> p[0], p[1] ...
 *   bgez  $v1, .L0011C158
 *    addiu $v0, $v0, 0x898             ; p += record stride
 *   jr    $ra
 *    addiu $v0, $zero, 0x1
 *
 * Same initialisation as func_0011C198, applied to records 1 and 0.
 */
struct R01C138 {
    char pad00[0x800];
    int  field800;      /* 0x800 */
    int  field804;      /* 0x804 */
    char field808[0x80];/* 0x808 */
    int  field888;      /* 0x888 */
    int  field88C;      /* 0x88C */
    int  field890;      /* 0x890 */
    int  field894;      /* 0x894 */
};

extern struct R01C138 D_0015DF48[];
extern char D_00138D08[];

int func_0011C138(void) {
    int i;

    for (i = 1; i >= 0; i--) {
        struct R01C138 *p = &D_0015DF48[i];

        p->field800 = -1;
        p->field804 = -1;
        p->field894 = 0;
        p->field888 = 1;
        p->field88C = 0;
        p->field890 = 0;
        p->field808[0] = D_00138D08[0];
        p->field808[1] = D_00138D08[1];
    }
    return 1;
}
