/* STATUS: NON_MATCHING (Session 4, 2026-10-14) - one instruction short.
 * `mult` matches with a runtime stride; 48 B vs 44 B. The original recomputes
 * the element address in the branch delay slot (`addu $v1,$a1,$a0`); ours reuses
 * the first computation.
 */
/* asm/cod/0220F8.s -> func_001220F8 @ 0x001220F8 (0x2C bytes)
 *   addiu $v0, $zero, 0x24
 *   lui   $v1, %hi(D_00163CC8)
 *   mult  $a0, $a0, $v0                 ; i * 0x24  (runtime stride)
 *   addiu $a1, $v1, %lo(D_00163CC8)
 *   addu  $v0, $a0, $a1
 *   lw    $v1, 0x0($v0)                 ; field0
 *   bnez  $v1, .Lfound
 *    addu $v1, $a1, $a0                  ; &D_00163CC8[i] (recomputed)
 *   jr    $ra
 *    addiu $v0, $zero, -0x1              ; return -1
 * .Lfound:
 *   jr    $ra
 *    lw   $v0, 0x4($v1)                  ; return field4
 */
struct S0220F8 {
    int  field0;    /* 0x0 */
    int  field4;    /* 0x4 */
    char pad08[0x1C];
};

extern struct S0220F8 D_00163CC8[];

int func_001220F8(int i) {
    int size = 0x24;
    struct S0220F8 *p = (struct S0220F8 *)((char *)D_00163CC8 + i * size);

    if (p->field0 == 0)
        return -1;
    return p->field4;
}
