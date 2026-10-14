/* Phase 3 flag-pinning case: branchy leaf, constant folded with masks.
 * asm/cod/0148B8.s -> func_001148B8 @ 0x001148B8 (0x28 bytes)
 *   addiu $v1, $zero, 7
 *   srl   $v0, $a0, 28
 *   bne   $v0, $v1, .L001148D8
 *    lui  $v0, (0xFFFFFFF >> 16)      <- branch delay slot
 *   lui   $v1, (0x80000000 >> 16)
 *   ori   $v0, $v0, (0xFFFFFFF & 0xFFFF)
 *   and   $a0, $a0, $v0
 *   or    $a0, $a0, $v1
 * .L001148D8:
 *   jr    $ra
 *    daddu $v0, $a0, $zero
 *
 * STATUS (2026-10-14): NON_MATCHING - the two-statement form below reproduces
 * every instruction except the emission order of the two `lui`s: the original
 * materialises the AND mask (0x0FFFFFFF) in the branch delay slot and the OR
 * mask (0x80000000) after it; our build emits them in the opposite order.
 * Unit size is identical (0x28 bytes).
 */
unsigned int func_001148B8(unsigned int x) {
    if ((x >> 28) == 7) {
        x &= 0x0FFFFFFF;
        x |= 0x80000000;
    }
    return x;
}
