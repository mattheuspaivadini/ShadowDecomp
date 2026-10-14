/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 5 [cc=29, default].
 * shape/allocation difference.
 * The original .s stays in the build (asm/cod/007D58.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/007D58.s -> func_00107D58 @ 0x00107D58 (0x34 bytes, 13 insns)
 *
 * Mode-select wrapper for func_00107C70 (the SIO2 register writer that polls
 * 0x1000F130 and stores the byte to 0x1000F180, see src/non_matching/007C70.c):
 *
 *   addiu $v0, $zero, 0xA
 *   bne   $a0, $v0, .L00107D80    ; a0 != 10 -> pass a0 through unchanged
 *   jal   func_00107C70           ; (a0 == 10) first write 0xD ...
 *    addiu $a0, $zero, 0xD
 *   ld    $ra, 0x0($sp)
 *   addiu $a0, $zero, 0xA         ; ... then 10
 *   j     func_00107C70
 *    addiu $sp, $sp, 0x10
 * .L00107D80:
 *   ld    $ra, 0x0($sp)
 *   j     func_00107C70           ; a0 passed straight through
 *    addiu $sp, $sp, 0x10
 *
 * Two *separate* tail-call sequences (the else path does not jump to the
 * fall-through's copy), so the source has two `return` statements; the
 * `addiu $a0,$zero,0xA` only exists on the ==10 path, which fixes the order of
 * the two literals. func_00107D58 returns int (declared `int func_00107D58(int
 * x);` by the matched caller 008D90.c).
 * MATCH GUESS: cc=296 (framed tail calls: sp,-0x10 + ld ra before the `j`)
 */
int func_00107C70(unsigned int value);

int func_00107D58(int a0) {
    if (a0 != 0xA)
        return func_00107C70(a0);
    func_00107C70(0xD);
    return func_00107C70(0xA);
}
