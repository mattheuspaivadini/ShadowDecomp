/* asm/cod/00FC08.s -> func_0010FC08 @ 0x0010FC08 (0x38 bytes)
 *   srl   $a2, $a2, 2
 *   beqz  $a2, .L0010FC38
 *    daddu $a3, $zero, $zero
 * .L0010FC18:
 *   lw    $v1, 0x0($a1)
 *   addiu $a3, $a3, 0x1
 *   addiu $a1, $a1, 0x4
 *   sltu  $v0, $a3, $a2
 *   sw    $v1, 0x0($a0)
 *   addiu $a0, $a0, 0x4
 *   bnez  $v0, .L0010FC18
 *    nop
 * .L0010FC38:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * Word copy: count is a byte size, divided by 4 (unsigned -> `srl`); a separate
 * index register is kept alongside the pointer increments; always returns 0.
 */
int func_0010FC08(unsigned int *dst, unsigned int *src, unsigned int size) {
    unsigned int i = 0;
    unsigned int count = size >> 2;

    if (count != 0) {
        do {
            *dst = *src;
            i++;
            src++;
            dst++;
        } while (i < count);
    }
    return 0;
}
