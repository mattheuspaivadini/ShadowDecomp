/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default].
 * tail call not emitted: cc=29 keeps jal+epilogue, but the original's 0x20 frame + `j` is the sibling-call shape (cc=296) with the 2.9 slot spacing. -mabi=eabi/-mgp64/-mips3 tried.
 * The original .s stays in the build (asm/cod/0101D8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0101D8.s -> func_001101D8 @ 0x001101D8 (0x28 bytes, 10 insns)
 *   addiu $sp, $sp, -0x20
 *   sd    $s0, 0x0($sp)
 *   sd    $ra, 0x10($sp)            ; 16-byte stack slots = the 2.9 frame shape
 *   jal   func_00110118             ; $a0 is left untouched (arg-less callee)
 *    daddu $s0, $a0, $zero          ; keep the argument across the call
 *   daddu $a0, $s0, $zero
 *   ld    $ra, 0x10($sp)
 *   ld    $s0, 0x0($sp)
 *   j     func_00106C00
 *    addiu $sp, $sp, 0x20
 *
 * Reached from `entry` (000010.s `j func_001101D8` with a0 = start(...)'s
 * result), so this is the post-startup init entry. It calls the func_00110118
 * trampoline (which `j`s to func_0010F550 - declared noreturn in the matched
 * 010118.c, which is why that C has no frame) and then tail-calls
 * func_00106C00 with the same argument.
 *
 * The `sd $s0, 0x0` / `sd $ra, 0x10` 0x20 frame is the 2.9 generation shape
 * (compare the matched 0188E0: same 0x20 frame, cc=29; 2.96 allocates 8-byte
 * apart slots).
 * MATCH GUESS: cc=29 */
void func_00110118(int a0);
int func_00106C00(int a0);

int func_001101D8(int a0) {
    int saved = a0;

    func_00110118(a0);
    return func_00106C00(saved);
}
