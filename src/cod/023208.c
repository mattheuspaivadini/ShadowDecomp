/* asm/cod/023208.s -> func_00123208 @ 0x00123208 (0x54 bytes, 21 insns)
 *
 * func_0010FB20-gated one-shot: swap the signed handle D_00135960 out before
 * releasing the lock, then put it back through the syscall stub:
 *
 *   a = func_0010FB20();              ; jal with an empty delay slot (nop)
 *   v = D_00135960;                   ; lw $s0,%lo(D_00135960)($v1)  (lui/%lo)
 *   D_00135960 = -1;                  ; addiu $a0,$zero,-1 ; sw in the beqz slot
 *   if (a != 0) func_0010FB70();      ; release
 *   if (v >= 0) func_00106FF0(v);     ; bltz $s0 -> skip
 *   return 0;                         ; daddu $v0,$zero,$zero
 *
 * `v` is live across the func_0010FB70() call, which is why it is kept in $s0
 * and the frame is 0x20 ($s0 + $ra). The `nop` in the first jal's delay slot
 * says this translation unit is -g2 (no delay-slot filling), unlike the
 * wave-2a siblings.
 * MATCH GUESS: cc=29 (the whole func_0010FB20 wrapper family, e.g. the matched
 * 010EA0.c/010DB8.c, is cc=29)
 */
int  DIntr(void);
int  EIntr(void);
int  DeleteSema(int a0);

extern int D_00135960[];   /* .data 0x00135960, 4 bytes - array => lui/%lo */

int func_00123208(void) {
    int a;
    int v;

    a = DIntr();
    v = D_00135960[0];
    D_00135960[0] = -1;
    if (a != 0)
        EIntr();
    if (v >= 0)
        DeleteSema(v);
    return 0;
}
