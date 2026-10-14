/* asm/cod/025998.s -> func_00125998 @ 0x00125998 (0x44 bytes)
 *   lbu   $v1, 0x0($a0)
 *   addiu $a0, $a0, 0x1
 *   daddu $a3, $zero, $zero       ; shift = 0
 *   andi  $v0, $v1, 0x80
 *   beqz  $v0, .L001259D0
 *    andi $a2, $v1, 0x7F          ; value = b & 0x7F
 * .L001259B0:
 *   lbu   $v1, 0x0($a0)
 *   addiu $a0, $a0, 0x1
 *   addiu $a3, $a3, 0x7           ; shift += 7
 *   andi  $v0, $v1, 0x7F
 *   andi  $v1, $v1, 0x80
 *   sllv  $v0, $v0, $a3
 *   bnez  $v1, .L001259B0
 *    or   $a2, $a2, $v0           ; value |= (b & 0x7F) << shift
 * .L001259D0:
 *   sw    $a2, 0x0($a1)
 *   jr    $ra
 *    daddu $v0, $a0, $zero        ; return p
 *
 * LEB128 unsigned decoder: reads a variable-length integer from `p`, stores it
 * at `*out`, returns the advanced pointer.
 */
unsigned char *func_00125998(unsigned char *p, int *out) {
    unsigned int b = *p++;
    int shift = 0;
    unsigned int value = b & 0x7F;

    while (b & 0x80) {
        b = *p++;
        shift += 7;
        value |= (b & 0x7F) << shift;
    }
    *out = value;
    return p;
}
