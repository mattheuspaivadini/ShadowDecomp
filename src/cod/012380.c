/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/012380/batch1.json (v01_paren_field0_plus16, cc=29, score 0).
 *
 * asm/cod/012380.s -> func_00112380 @ 0x00112380 (0x3C bytes)
 *   daddu $a1, $a0, $zero
 *   lw    $v0, 0x4($a1)      ; p->field4
 *   lw    $a0, 0xC($a1)      ; p->fieldC
 *   lw    $v1, 0x0($a1)      ; p->field0
 *   addiu $v0, $v0, 0x1
 *   addiu $a0, $a0, 0x1
 *   sw    $v0, 0x4($a1)      ; p->field4 = field4 + 1
 *   addiu $v1, $v1, 0x10     ; field0 + 16
 *   addu  $v1, $a1, $v1      ; p + (field0 + 16)
 *   bne   $a0, $v1, .Lend
 *    sw   $a0, 0xC($a1)      ; p->fieldC = fieldC + 1
 *   addiu $v0, $a1, 0x10
 *   sw    $v0, 0xC($a1)      ; p->fieldC = p + 16
 * .Lend:
 *   jr    $ra
 *    nop
 *
 * Matching notes:
 * - the comparison's arithmetic must be grouped as `p->field0 + 16` BEFORE the
 *   pointer add, i.e. `(char *)p + (p->field0 + 16)`. The unparenthesised
 *   `(char *)p + p->field0 + 16` associates left and the two operations come
 *   out transposed (score 2);
 * - cc=29 only (the whole `mult`-address family); cc=296 scores 12.
 * Offsets 0x0/0x4/0xC are evidence-backed; the struct's meaning is UNCONFIRMED
 * (ring-cursor advance).
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
    if (p->fieldC == (int)((char *)p + (p->field0 + 16)))
        p->fieldC = (int)((char *)p + 16);
}
