/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=29, default].
 * field mask sequence; load/store order differs.
 * The original .s stays in the build (asm/cod/014DA0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/014DA0.s -> func_00114DA0 @ 0x00114DA0 (0x48 bytes, 18 insns)
 * libdma-style channel helper: after waiting on func_001147C0(p) (which spins
 * on p[0] & 0x100), it clears p[8] (0x20) and re-programs p[0] with the
 * three masks taken from the asm:
 *   v = p[0];
 *   p[8] = 0;
 *   v = (v & ~0xC) | 0x4;      (addiu $v1,$zero,-0xD  -> $v1 = 0xFFFFFFF3)
 *   v = (v & ~0x1) | 0x100;    (addiu $a0,$zero,-0x2  -> $a0 = 0xFFFFFFFE)
 *   p[0] = v;
 * The `sw $zero,0x20($s0)` is scheduled between the load and the `and` chain,
 * i.e. it is the second statement.  Field roles UNCONFIRMED.
 * MATCH GUESS: cc=296 (014C30/014FF0 in this block are 2.96; weak) */
extern void func_001147C0(int *p);

void func_00114DA0(int *p) {
    int v;

    func_001147C0(p);
    v = p[0];
    p[8] = 0;
    v = (v & ~0xC) | 0x4;
    v = (v & ~0x1) | 0x100;
    p[0] = v;
}
