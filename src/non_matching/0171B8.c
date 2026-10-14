/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 14 [cc=29, default].
 * $gp save/restore around an indirect call (the 0092F8/00A878 family) is not emitted for plain C.
 * The original .s stays in the build (asm/cod/0171B8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0171B8.s -> func_001171B8 @ 0x001171B8 (0x54 bytes, 21 insns)
 *
 * Invoke the cross-module entry registered by func_00117138:
 *
 *   if (D_00150E08 == 0) return;        ; beqz -> first epilogue label
 *   if (D_00133A64 != 0) return;        ; bnez -> ld $s0 label
 *   $s0 = $gp; $gp = D_00150E0C;        ; the callee's global pointer
 *   jalr $a1                            ; $a1 = D_00150E08
 *    $a0 = D_00150E10                   ; (delay slot) the argument
 *   $gp = $s0;                          ; daddu $gp,$s0,$zero
 *
 * func_00117138 stores the triplet (entry, $gp, argument) into
 * D_00150E08/D_00150E0C/D_00150E10, so the call must run with the module's own
 * $gp - hence the save/restore dance around the `jalr`.
 *
 * RESIDUAL: that dance is the reason this draft cannot be byte-exact. ee-gcc
 * does not emit `daddu $s0,$gp` / `lw $gp,...` / `jalr` / `daddu $gp,$s0` for
 * any plain C call (the loaded $gp comes from a *user* object, not from the
 * abicalls `_gp_disp` sequence), which is why the whole family is still
 * unmatched: asm/cod/0092F8/00A878/011CA8/012E80/016D88/019AC0 all share this
 * idiom. It is either hand-written asm or an inline-asm macro; the C below
 * reproduces the guards, the argument load and the call, but allocates a 0x10
 * frame (no $s0) instead of the original's 0x20/$s0 frame.
 * MATCH GUESS: cc=296
 */
extern int D_00150E08[];   /* .bss 0x00150E08: installed entry address */
extern int D_00150E0C[];   /* .bss 0x00150E0C: module $gp value */
extern int D_00150E10[];   /* .bss 0x00150E10: argument for the entry */
extern int D_00133A64[];   /* .data 0x00133A64: in-use guard word */

void func_001171B8(void) {
    if (D_00150E08[0] == 0)
        return;
    if (D_00133A64[0] != 0)
        return;
    ((void (*)(int))D_00150E08[0])(D_00150E10[0]);
}
