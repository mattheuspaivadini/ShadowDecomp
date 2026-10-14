/* MATCHING (Session 4, 2026-10-14): byte-exact only with the ALTERNATE EE-GCC
 * revision `ee-gcc2.9-991111-01` (manifest token `cc=29`). Evidence:
 * tools/cc_matrix.py, docs/compiler.md section 4.3.
 *
 * asm/cod/00FFC0.s -> func_0010FFC0 @ 0x0010FFC0 (0x30 bytes)
 *   beqz  $a2, .L0010FFE8
 *    daddu $a3, $zero, $zero
 * .L0010FFC8:
 *   lbu   $v1, 0x0($a1)
 *   addiu $a3, $a3, 0x1
 *   addiu $a1, $a1, 0x1
 *   sltu  $v0, $a3, $a2
 *   sb    $v1, 0x0($a0)
 *   addiu $a0, $a0, 0x1
 *   bnez  $v0, .L0010FFC8
 *    nop
 * .L0010FFE8:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * A byte copy loop that pointer-increments both operands and keeps a separate
 * count register; it always returns 0.
 */
int func_0010FFC0(unsigned char *dst, unsigned char *src, unsigned int count) {
    unsigned int i = 0;

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
