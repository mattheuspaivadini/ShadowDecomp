/* STATUS: NON_MATCHING (Session 4, 2026-10-14).
 * 12/15 instructions differ: the original loads p->field4, then fieldC, then
 * field0, stores field4 first and computes `p + 16` only on the taken path.
 * Ours reorders the loads (field0 first) and hoists `p + 16`; two source
 * orderings tried. Allocation/scheduling family (docs/compiler.md section 4).
 */
/* asm/cod/012380.s -> func_00112380 @ 0x00112380 (0x3C bytes)
 *   daddu $a1, $a0, $zero
 *   lw    $v0, 0x4($a1)      ; p->field4
 *   lw    $a0, 0xC($a1)      ; p->fieldC
 *   lw    $v1, 0x0($a1)      ; p->field0
 *   addiu $v0, $v0, 0x1
 *   addiu $a0, $a0, 0x1
 *   sw    $v0, 0x4($a1)      ; p->field4 = field4 + 1
 *   addiu $v1, $v1, 0x10
 *   addu  $v1, $a1, $v1      ; p + field0 + 16
 *   bne   $a0, $v1, .Lend
 *    sw   $a0, 0xC($a1)      ; p->fieldC = fieldC + 1
 *   addiu $v0, $a1, 0x10
 *   sw    $v0, 0xC($a1)      ; p->fieldC = p + 16
 * .Lend:
 *   jr    $ra
 *    nop
 *
 * The load order (field4, fieldC, field0) is evidence-backed: the source must
 * use field4 first. Offsets 0x0/0x4/0xC are evidence-backed; the struct's
 * meaning is UNCONFIRMED (ring-cursor advance).
 */
struct S012380 {
    int field0;   /* 0x0 */
    int field4;   /* 0x4 */
    int field8;   /* 0x8 */
    int fieldC;   /* 0xC */
};

void func_00112380(struct S012380 *p) {
    p->field4 = p->field4 + 1;
    p->fieldC = p->fieldC + 1;
    if (p->fieldC == (int)((char *)p + p->field0 + 16))
        p->fieldC = (int)((char *)p + 16);
}
