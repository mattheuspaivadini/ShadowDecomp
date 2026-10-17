/* asm/cod/008E88.s -> sceVprintf.
 * SCE sceVprintf; unsigned 0xFFFFFFFF limit (GAS li -> lui/ori) (Session 19)
 * MATCHED. */
/* asm/cod/008E88.s -> sceVprintf @ 0x00108E88 (0x70 bytes, 28 insns)
 *
 * func_00107FF8-callback wrapper behind the DIntr guard (the 008Dxx /
 * 008Exx family):
 *   g = DIntr();                 ; critical-section guard (=$s0)
 *   buf = 0;                             ; sw $zero,0x0($sp)
 *   func_00107FF8(func_00108D68, &buf, 0xFFFFFFFF, a0, a1);
 *   if (g != 0)
 *       EIntr();                 ; release
 * a0/a1 are parked in $s1/$s2 before the guard call (they are the 4th/5th
 * arguments of func_00107FF8: `daddu $a3,$s1,$zero`, `daddu $a4,$s2,$zero`).
 * Nothing is copied out at the end, so the function is void (the epilogue keeps
 * whatever $v0 the last call left - the same shape as the sibling 008E40 /
 * 008EF8). The 0xFFFFFFFF third argument is the lui/ori materialisation (the
 * 2.9 generation; a signed `-1` would be `addiu $a2,$zero,-1`, see the matched
 * 0231A8), hence the unsigned literal.
 * MATCH GUESS: cc=29 (the DIntr wrapper family, e.g. the matched 010F40)
 */
int DIntr(void);
int EIntr(void);
int func_00107FF8(int (*cb)(), int *p, unsigned int a1, int a2, int a3);
int func_00108D68(int a, int b, int c);

void sceVprintf(int a0, int a1) {
    int buf;
    int g;

    buf = 0;
    g = DIntr();
    func_00107FF8(func_00108D68, &buf, 0xFFFFFFFF, a0, a1);
    if (g != 0)
        EIntr();
}
