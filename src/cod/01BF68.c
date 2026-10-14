/* asm/cod/01BF68.s -> func_0011BF68 @ 0x0011BF68 (0x44 bytes)
 *   daddu $a1, $a0, $zero        ; p = s
 *   daddu $a2, $zero, $zero      ; n = 0
 *   lb    $v0, 0x0($a1)
 *   beqz  $v0, .L0011BFA4
 *    lbu  $v1, 0x0($a1)
 * .L0011BF80:
 *   sll   $v0, $v1, 24
 *   addiu $a1, $a1, 0x1
 *   sra   $v0, $v0, 24           ; (signed char)*p
 *   addiu $v1, $a2, 0x1          ; n + 1
 *   xori  $v0, $v0, 0x2F         ; c ^ '/'
 *   lb    $a0, 0x0($a1)
 *   movz  $a2, $v1, $v0          ; if (c == '/') n = n + 1
 *   bnez  $a0, .L0011BF80
 *    lbu  $v1, 0x0($a1)
 * .L0011BFA4:
 *   jr    $ra
 *    daddu $v0, $a2, $zero
 *
 * Count the occurrences of '/' in a NUL-terminated string.
 */
int func_0011BF68(const char *s) {
    int n = 0;

    while (*s) {
        if (*s == '/')
            n++;
        s++;
    }
    return n;
}
