/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/0123C0/batch1.json (v01_paren_field0_plus16, cc=29, score 0).
 *
 * asm/cod/0123C0.s -> func_001123C0 @ 0x001123C0 (0x3C bytes)
 *   daddu $a1, $a0, $zero
 *   lw    $v0, 0x4($a1)      ; p->field4
 *   lw    $a0, 0x8($a1)      ; p->field8
 *   lw    $v1, 0x0($a1)      ; p->field0
 *   addiu $v0, $v0, -0x1
 *   addiu $a0, $a0, 0x1
 *   sw    $v0, 0x4($a1)      ; p->field4 = field4 - 1
 *   addiu $v1, $v1, 0x10     ; field0 + 16
 *   addu  $v1, $a1, $v1      ; p + (field0 + 16)
 *   bne   $a0, $v1, .Lend
 *    sw   $a0, 0x8($a1)      ; p->field8 = field8 + 1
 *   addiu $v0, $a1, 0x10
 *   sw    $v0, 0x8($a1)      ; p->field8 = p + 16
 * .Lend:
 *   jr    $ra
 *    nop
 *
 * Matching notes: same as func_00112380 — `(char *)p + (p->field0 + 16)`
 * (int add first), cc=29 only.
 */
struct S0123C0 {
    int field0;   /* 0x0 */
    int field4;   /* 0x4 */
    int field8;   /* 0x8 */
};

void func_001123C0(struct S0123C0 *p) {
    p->field4 = p->field4 - 1;
    p->field8 = p->field8 + 1;
    if (p->field8 == (int)((char *)p + (p->field0 + 16)))
        p->field8 = (int)((char *)p + 16);
}
