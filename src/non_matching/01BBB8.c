/* STATUS (Session 4, 2026-10-14): NON_MATCHING. string validator; the `lbu`+sign-extend spelling and delay-slot scheduling differ.
 * The original .s stays in the build (asm/cod/01BBB8.s); this C
 * attempt is kept for the record. */
/* asm/cod/01BBB8.s -> func_0011BBB8 @ 0x0011BBB8 (0x54 bytes)
 *   lb    $v0, 0x0($a0)
 *   beqz  $v0, .L0011BC04
 *    lbu  $v1, 0x0($a0)
 *   addiu $a2, $zero, 0x3F            ; '?'
 *   addiu $a1, $zero, 0x2A            ; '*'
 * .L0011BBD0:
 *   sll   $v0, $v1, 24
 *   sra   $v0, $v0, 24                ; (signed char)*s
 *   beq   $v0, $a2, .L0011BBF0
 *    nop
 *   beq   $v0, $a1, .L0011BBF0
 *    slti $v0, $v0, 0x20
 *   beqz  $v0, .L0011BBF8
 *    addiu $a0, $a0, 0x1
 * .L0011BBF0:
 *   jr    $ra
 *    daddu $v0, $zero, $zero          ; return 0
 * .L0011BBF8:
 *   lb    $v0, 0x0($a0)
 *   bnez  $v0, .L0011BBD0
 *    lbu  $v1, 0x0($a0)
 * .L0011BC04:
 *   jr    $ra
 *    addiu $v0, $zero, 0x1            ; return 1
 *
 * Validate a string: returns 0 if it contains '?', '*' or a control character
 * (< 0x20), 1 otherwise. The character is loaded as a byte and sign-extended.
 */
int func_0011BBB8(const unsigned char *s) {
    signed char c;

    while ((c = (signed char)*s) != 0) {
        if (c == '?' || c == '*' || c < 0x20)
            return 0;
        s++;
    }
    return 1;
}
