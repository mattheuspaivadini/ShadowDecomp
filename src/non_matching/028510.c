/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=296, default].
 * refcount decrement + gated tail call.
 * The original .s stays in the build (asm/cod/028510.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/028510.s -> func_00128510 @ 0x00128510 (0x4C bytes, 19 insns)
 *
 * Refcount release: decrement D_001360C4, return the new value, and when it
 * reaches zero clear D_001360C0 to -1 and tail-call the syscall-0x42 stub
 * func_00107000 with D_001329A0 (a handle/id word) as its argument.
 *
 * `bnez $v0, .L00128550` with `sw $v0, 0x0($v1)` in the delay slot: the
 * decremented value is both the returned value and the stored value, so it is
 * kept in a local. The tail call is the framed shape (the `ld $ra` is emitted
 * before the `j`, the `addiu $sp` sits in the `j` delay slot), i.e. gcc
 * sibling-call optimisation with a real frame.
 * MATCH GUESS: cc=296 (framed `j` after the `ld $ra`)
 */
extern int D_001360C4 __attribute__((section(".data")));
extern int D_001360C0 __attribute__((section(".data")));
extern int D_001329A0 __attribute__((section(".data")));

int func_00107000(int a0);

int func_00128510(void) {
    int r;

    r = D_001360C4 - 1;
    D_001360C4 = r;
    if (r == 0) {
        D_001360C0 = -1;
        return func_00107000(D_001329A0);
    }
    return r;
}
