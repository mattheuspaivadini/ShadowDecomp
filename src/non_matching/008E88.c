/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 11 [cc=29, default].
 * gated func_00107FF8 call with -1 argument.
 * The original .s stays in the build (asm/cod/008E88.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/008E88.s -> func_00108E88 @ 0x00108E88 (0x70 bytes, 28 insns)
 *
 * func_00107FF8-callback wrapper behind the func_0010FB20 guard (the 008Dxx /
 * 008Exx family):
 *   g = func_0010FB20();                 ; critical-section guard (=$s0)
 *   buf = 0;                             ; sw $zero,0x0($sp)
 *   func_00107FF8(func_00108D68, &buf, 0xFFFFFFFF, a0, a1);
 *   if (g != 0)
 *       func_0010FB70();                 ; release
 * a0/a1 are parked in $s1/$s2 before the guard call (they are the 4th/5th
 * arguments of func_00107FF8: `daddu $a3,$s1,$zero`, `daddu $a4,$s2,$zero`).
 * Nothing is copied out at the end, so the function is void (the epilogue keeps
 * whatever $v0 the last call left - the same shape as the sibling 008E40 /
 * 008EF8). The 0xFFFFFFFF third argument is the lui/ori materialisation (the
 * 2.9 generation; a signed `-1` would be `addiu $a2,$zero,-1`, see the matched
 * 0231A8), hence the unsigned literal.
 * MATCH GUESS: cc=29 (the func_0010FB20 wrapper family, e.g. the matched 010F40)
 */
int func_0010FB20(void);
int func_0010FB70(void);
int func_00107FF8(int (*cb)(), int *p, int a1, int a2, int a3);
int func_00108D68(int a, int b, int c);

void func_00108E88(int a0, int a1) {
    int buf;
    int g;

    buf = 0;
    g = func_0010FB20();
    func_00107FF8(func_00108D68, &buf, 0xFFFFFFFF, a0, a1);
    if (g != 0)
        func_0010FB70();
}
