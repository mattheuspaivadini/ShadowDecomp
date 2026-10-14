/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 4 [cc=29, default].
 * loader helper + func_00106C30 tail.
 * The original .s stays in the build (asm/cod/010120.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/010120.s -> func_00110120 @ 0x00110120 (0x70 bytes, 28 insns)
 *
 * Four-argument member of the 010190/010200 loader+syscall family:
 *   func_00110000(&D_00138270, a2, a3);                    ; pack the source
 *   func_00110118();                                       ; tail-calls func_0010F550
 *   func_00106C30(a0, a1, a2, D_001326B0[0] + 4);           ; syscall, tail call
 * a0..a2 are parked in $s1/$s2/$s0 before the first call (only a2/a3 are used
 * there, but the last call needs all three); D_001326B0 is reloaded after the
 * middle call and `+ 4` is folded into the same `addiu $a3,$a3,0x4`.
 * MATCH GUESS: cc=29 (010190/010200 are cc=29; same 0x10-spaced slot layout)
 */
extern int D_00138270[];   /* .rodata 0x00138270: 2 words, address taken */
extern int D_001326B0[];   /* .data   0x001326B0 (non-small) */

int func_00110000(int *p, int a0, int a1);
void func_00110118(void);
void func_00106C30(int a0, int a1, int a2, int a3);

void func_00110120(int a0, int a1, int a2, int a3) {
    func_00110000(D_00138270, a2, a3);
    func_00110118();
    func_00106C30(a0, a1, a2, D_001326B0[0] + 4);
}
