/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 3 [cc=29, default].
 * flag clear + two bounds-checked clears; constant materialisation order (lui a0) differs.
 * The original .s stays in the build (asm/cod/0199C8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0199C8.s -> func_001199C8 @ 0x001199C8 (0x30 bytes, 10 insns)
 *
 * Clear the libmrpc word at D_00135618, then hand two negative "index"
 * constants to the two bounds-checked table-clearing helpers (see the matched
 * 011C50.c: a negative index selects the fallback table at D_0014AC88 and the
 * low bits become the byte offset):
 *
 *   lui   $v0, %hi(D_00135618)            ; array decl -> absolute addressing
 *   sw    $zero, %lo(D_00135618)($v0)     ; D_00135618 = 0
 *   jal   func_00112C78                   ; func_00112C78(0x80000018)
 *    ori  $a0, $a0, 0x18
 *   ld    $ra, 0x0($sp)
 *   j     func_00111C50                   ; tail call with 0x80000014
 *    addiu $sp, $sp, 0x10
 *
 * The framed `j` (`addiu sp,-0x10; sd ra; ld ra; j target; addiu sp,+0x10`) is
 * the cc=296 sibling-call shape (compare the matched 003008.c trampoline), so
 * the second call is a real `return`; the first call is a plain statement.
 * No caller exists in the image, so the int return type is UNCONFIRMED (it just
 * passes func_00111C50's status through).
 * MATCH GUESS: cc=296
 */
extern int D_00135618[];    /* .data 0x00135618: array => lui/%lo, not %gp_rel */

int sceSifRemoveCmdHandler(int index);
int sceSifRemoveRebootNotifyHandler(int index);

int sceSifMExitRpc(void) {
    D_00135618[0] = 0;
    sceSifRemoveCmdHandler((int)0x80000018);
    return sceSifRemoveRebootNotifyHandler((int)0x80000014);
}
