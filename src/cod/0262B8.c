/* MATCHED (Session 5, step 1). Evidence: tools/permute.py ->
 * build/permute/0262B8/batch2.json (v04_field_test, cc=296, score 0).
 *
 * asm/cod/0262B8.s -> func_001262B8 @ 0x001262B8 (0x44 bytes)
 *   lw    $a1, 0x0($a0)                ; n = p->field0
 *   beqz  $a1, .Lend
 *    daddu $a2, $zero, $zero           ; count = 0
 * .Lloop:
 *   lw    $v0, 0x4($a0)                ; p->field4
 *   beqz  $v0, .Lskip
 *    addiu $v0, $a2, 0x1
 *   lw    $v1, 0x8($a0)                ; p->field8
 *   movn  $a2, $v0, $v1                ; if (p->field8) count = count + 1
 * .Lskip:
 *   addu  $v0, $a0, $a1                ; p + n
 *   addiu $a0, $v0, 0x4
 *   lw    $v1, 0x0($a0)                ; n = p->field0
 *   bnez  $v1, .Lloop
 *    daddu $a1, $v1, $zero
 * .Lend:
 *   jr    $ra
 *    daddu $v0, $a2, $zero             ; return count
 *
 * Matching note: the loop must re-read `p->field0` in the condition
 * (`while (p->field0 != 0)`) instead of carrying an `n` local: the carried
 * local lets ee-gcc rotate the loop into `bnezl` with the body load in the
 * delay slot (4 bytes short). cc=296. Offsets 0x0/0x4/0x8 are evidence-backed;
 * the node type is UNCONFIRMED (variable-stride list, step `n + 4`).
 */
struct S0262B8 {
    int field0;   /* 0x0 */
    int field4;   /* 0x4 */
    int field8;   /* 0x8 */
};

int func_001262B8(struct S0262B8 *p) {
    int count = 0;

    while (p->field0 != 0) {
        if (p->field4 != 0) {
            if (p->field8 != 0)
                count++;
        }
        p = (struct S0262B8 *)((char *)p + p->field0 + 4);
    }
    return count;
}
