/* asm/cod/00FC40.s -> func_0010FC40 @ 0x0010FC40 (0x40 bytes)
 *   lw    $v0, 0x0($a0)
 *   beq   $v0, $a2, .L0010FC74
 *    sltu $v0, $a0, $a1
 *   beql  $v0, $zero, .L0010FC78
 *    movz $a0, $zero, $v0
 *   addiu $a0, $a0, 0x4
 * .L0010FC58:
 *   lw    $v0, 0x0($a0)
 *   beq   $v0, $a2, .L0010FC74
 *    sltu $v0, $a0, $a1
 *   bnel  $v0, $zero, .L0010FC58
 *    addiu $a0, $a0, 0x4
 *   b     .L0010FC78
 *    movz $a0, $zero, $v0
 * .L0010FC74:
 *   movz  $a0, $zero, $v0
 * .L0010FC78:
 *   jr    $ra
 *    daddu $v0, $a0, $zero
 *
 * Linear search of `key` in [p, end); returns the matching pointer or NULL.
 * The key test is done first, the bounds check only when it misses.
 */
int *func_0010FC40(int *p, int *end, int key) {
    while (*p != key) {
        if (p >= end)
            return 0;
        p++;
    }
    return p;
}
