/* asm/cod/02F800.s -> func_0012F800 @ 0x0012F800 (0x34 bytes, 12 insns)
 *
 * State check + dispatch:
 *
 *   addiu $v1, $zero, 0x9
 *   lhu   $v0, 0xC($a0)               ; unsigned halfword at p+0xC
 *   andi  $v0, $v0, 0x9               ; keep bits 0 and 3
 *   bne   $v0, $v1, .L0012F828        ; != 9 -> return 0
 *   j     func_0012D6D8               ; both bits set: forward $a0 unchanged
 *    addiu $sp, $sp, 0x10
 * .L0012F828:
 *   daddu $v0, $zero, $zero
 *   jr    $ra
 *    addiu $sp, $sp, 0x10
 *
 * `lhu` + `andi 0x9` + the compare against 9 written directly give the
 * `(x & 9) == 9` shape. The tail call touches no argument register at all, so
 * the same pointer is forwarded; func_0012D6D8 is the callback that also
 * installs itself as a function pointer (asm/cod/02D6D8.s).
 * The framed `j` (`sp,-0x10; sd ra; ld ra; j target; sp,+0x10`) is the cc=296
 * sibling-call shape (matched 003008.c); the return type of the callee is
 * UNCONFIRMED (int assumed, only its value is forwarded).
 * MATCH GUESS: cc=296
 */
int func_0012D6D8(unsigned char *p);

int func_0012F800(unsigned char *p) {
    if ((*(unsigned short *)(p + 0xC) & 9) == 9)
        return func_0012D6D8(p);
    return 0;
}
