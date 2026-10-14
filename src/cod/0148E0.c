/* asm/cod/0148E0.s -> func_001148E0 @ 0x001148E0 (0x34 bytes)
 *   beqz  $a1, .L0011490C
 *    addiu $v0, $a1, -0x1        ; v0 = n - 1
 *   addiu $v1, $zero, -0x1       ; v1 = -1
 * .L001148F0:
 *   sb    $zero, 0x0($a0)
 *   addiu $v0, $v0, -0x1         ; v0--
 *   addiu $a0, $a0, 0x1
 *   bne   $v0, $v1, .L001148F0
 *    nop
 * .L0011490C:
 *   jr    $ra
 *    nop
 *
 * Zero `n` bytes.
 */
void func_001148E0(unsigned char *p, int n) {
    int i = n - 1;

    if (n != 0) {
        do {
            *p++ = 0;
        } while (--i != -1);
    }
}
