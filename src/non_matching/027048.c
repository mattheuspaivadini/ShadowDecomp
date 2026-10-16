/* STATUS (Session 4, 2026-10-14): NON_MATCHING. float decompose; `mant << 7` placement and register roles differ.
 * The original .s stays in the build (asm/cod/027048.s); this C
 * attempt is kept for the record. */
/* asm/cod/027048.s -> func_00127048 @ 0x00127048 (0x5C bytes)
 *   lw    $v1, 0x0($a0)                ; bits = *in
 *   lui   $a0, 0x7FFFFF
 *   ori   $a0, $a0, 0xFFFF
 *   daddu $a2, $a1, $zero              ; out
 *   srl   $v0, $v1, 23
 *   srl   $a1, $v1, 31
 *   andi  $v0, $v0, 0xFF               ; exp
 *   and   $v1, $v1, $a0                ; mantissa
 *   sw    $a1, 0x4($a2)                ; out[1] = sign
 *   addiu $a1, $v0, -0x7F              ; exp - 0x7F
 *   bnez  $v0, .L00127088
 *    sll  $a0, $v1, 7                  ; mant << 7
 *   addiu $v0, $zero, 0x2
 *   jr    $ra
 *    sw   $v0, 0x0($a2)                ; out[0] = 2
 * .L00127088:
 *   lui   $v0, 0x40000000
 *   addiu $v1, $zero, 0x3
 *   or    $v0, $a0, $v0
 *   sw    $a1, 0x8($a2)                ; out[2] = exp - 0x7F
 *   sw    $v1, 0x0($a2)                ; out[0] = 3
 *   jr    $ra
 *    sw   $v0, 0xC($a2)                ; out[3]
 *
 * Decompose the 32-bit IEEE754 word at *in into {type, sign, exp, mantissa}.
 */
int __unpack_f(unsigned int *in, int *out) {
    unsigned int bits = *in;
    unsigned int exp = (bits >> 23) & 0xFF;
    unsigned int sign = bits >> 31;
    unsigned int mant = bits & 0x7FFFFF;

    out[1] = sign;
    if (exp == 0) {
        out[0] = 2;
        return 2;
    }
    out[2] = exp - 0x7F;
    out[0] = 3;
    out[3] = (mant << 7) | 0x40000000;
    return 3;
}
