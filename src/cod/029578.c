/* asm/cod/029578.s -> func_00129578 @ 0x00129578 (0x50 bytes)
 *   lbu   $v1, 0x0($a0)
 *   sll   $a1, $a1, 24
 *   sra   $a1, $a1, 24                 ; c = (signed char)arg
 *   daddu $a2, $zero, $zero            ; found = 0
 *   beqz  $v1, .L001295B0
 *    daddu $v0, $v1, $zero
 * .L00129590:
 *   sll   $v0, $v0, 24
 *   sra   $v0, $v0, 24
 *   xor   $v0, $v0, $a1
 *   movz  $a2, $a0, $v0                ; if (*p == c) found = p
 *   addiu $a0, $a0, 0x1
 *   lbu   $v1, 0x0($a0)
 *   bnez  $v1, .L00129590
 *    daddu $v0, $v1, $zero
 * .L001295B0:
 *   sll   $v1, $v1, 24
 *   daddu $v0, $a0, $zero
 *   sra   $v1, $v1, 24
 *   xor   $v1, $v1, $a1
 *   jr    $ra
 *    movn $v0, $a2, $v1                ; if ((signed char)*p != c) return found
 *
 * Manual strrchr: remembers the last position where the character matches, and
 * returns the end pointer when the terminator itself matches (c == 0).
 */
char *func_00129578(const char *s, int arg) {
    char *p = (char *)s;
    char *found = 0;
    signed char c = arg;

    while (*p) {
        if ((signed char)*p == c)
            found = p;
        p++;
    }
    return ((signed char)*p == c) ? p : found;
}
