/* asm/cod/0259E0.s -> func_001259E0 @ 0x001259E0 (0x58 bytes)
 *   daddu $a7, $zero, $zero           ; shift = 0
 *   daddu $a4, $zero, $zero           ; value = 0
 * .L001259E8:
 *   lbu   $a2, 0x0($a0)
 *   addiu $a0, $a0, 0x1
 *   andi  $v0, $a2, 0x7F
 *   andi  $v1, $a2, 0x80
 *   sllv  $v0, $v0, $a7
 *   addiu $a7, $a7, 0x7
 *   bnez  $v1, .L001259E8
 *    or   $a4, $a4, $v0
 *   sltiu $v0, $a7, 0x20
 *   beql  $v0, $zero, .L00125A30
 *    sw   $a4, 0x0($a1)
 *   andi  $v0, $a2, 0x40
 *   beql  $v0, $zero, .L00125A30
 *    sw   $a4, 0x0($a1)
 *   addiu $v0, $zero, -0x1
 *   sllv  $v0, $v0, $a7
 *   or    $a4, $a4, $v0
 *   sw    $a4, 0x0($a1)
 * .L00125A30:
 *   jr    $ra
 *    daddu $v0, $a0, $zero            ; return p
 *
 * Signed LEB128 decoder: reads a variable-length value, sign-extends it when
 * the encoding is shorter than 32 bits and the sign bit (0x40) is set, stores
 * it and returns the advanced pointer.
 */
unsigned char *func_001259E0(unsigned char *p, int *out) {
    int shift = 0;
    unsigned int value = 0;
    unsigned char b;

    do {
        b = *p++;
        value |= (b & 0x7F) << shift;
        shift += 7;
    } while (b & 0x80);
    if ((unsigned int)shift < 32u && (b & 0x40))
        value |= 0xFFFFFFFFu << shift;
    *out = value;
    return p;
}
