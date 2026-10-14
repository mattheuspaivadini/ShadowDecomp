/* asm/cod/01BAE8.s -> func_0011BAE8 @ 0x0011BAE8 (0x5C bytes)
 *   sll   $a1, $a1, 24
 *   lb    $v1, 0x0($a0)
 *   lbu   $v0, 0x0($a0)
 *   sra   $a1, $a1, 24                 ; c = (signed char)arg
 *   beqz  $v1, .L0011BB24
 *    daddu $a2, $a0, $zero             ; p = s
 *   beq   $v1, $a1, .L0011BB34
 * .L0011BB10:
 *   lb    $v1, 0x0($a2)
 *   beqz  $v1, .L0011BB24
 *    lbu  $v0, 0x0($a2)
 *   bnel  $v1, $a1, .L0011BB10
 *    addiu $a2, $a2, 0x1
 * .L0011BB24:
 *   sll   $v0, $v0, 24
 *   sra   $v0, $v0, 24
 *   bne   $v0, $a1, .L0011BB3C
 * .L0011BB34:
 *   jr    $ra
 *    subu $v0, $a2, $a0                ; return p - s
 * .L0011BB3C:
 *   jr    $ra
 *    addiu $v0, $zero, -0x1
 *
 * Character search returning the offset of the match, or -1. The terminator is
 * also compared (a NUL search returns the string length).
 */
int func_0011BAE8(const char *s, int arg) {
    signed char c = arg;
    const char *p = s;

    while (*p) {
        if (*p == c)
            return p - s;
        p++;
    }
    return ((signed char)*p == c) ? (p - s) : -1;
}
