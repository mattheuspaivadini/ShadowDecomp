/* STATUS: NON_MATCHING (Session 4, 2026-10-14) - 4 bytes short.
 * The whole body matches (including the `movn` for the double condition); only
 * the loop tail differs. The original ends the loop with
 * `lw $v1,0($a0); bnez $v1,.Lloop; daddu $a1,$v1,$zero`, while ee-gcc2.96
 * rotates the loop: `bnezl $a1,.Lloop` with the body's first load in the delay
 * slot. Tried `while`/`do-while`/`for` spellings and `-g0`; identical result.
 */
/* asm/cod/0262B8.s -> func_001262B8 @ 0x001262B8 (0x40 bytes)
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
 * The three offsets 0x0/0x4/0x8 are evidence-backed; the list node type is
 * UNCONFIRMED (it is a variable-stride list walked with `p + n + 4`).
 */
struct S0262B8 {
    int field0;   /* 0x0 */
    int field4;   /* 0x4 */
    int field8;   /* 0x8 */
};

int func_001262B8(struct S0262B8 *p) {
    int count = 0;
    int n = p->field0;

    while (n != 0) {
        if (p->field4 != 0) {
            if (p->field8 != 0)
                count++;
        }
        p = (struct S0262B8 *)((char *)p + n + 4);
        n = p->field0;
    }
    return count;
}
