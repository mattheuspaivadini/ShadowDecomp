/* asm/cod/003F28.s -> func_00103F28 @ 0x00103F28 (0x70 bytes, 28 insns)
 *
 * Flush the 10-entry callback table D_0013CFA0 (the table filled by the matched
 * func_00103F98 when the counter D_0013A07C hits 10) and reset the counter:
 *
 *   addiu $s2,$hi(D_0013CFA0)             ; keep the %hi half in $s2
 *   addiu $s0,$s2,%lo(D_0013CFA0)         ; p = D_0013CFA0
 *   addiu $s1,$zero,0x9                   ; i = 9
 *   lw    $v0,0x0($s0)                    ; *p (rotated to the loop bottom)
 * .Lloop:
 *   beqz  $v0,.Lnext / addiu $s0,$s0,0x4  ; if (f) f();  (p++ in the slot)
 *   jalr  $v0 / nop
 * .Lnext:
 *   addiu $s1,$s1,-1
 *   bgezl $s1,.Lloop / lw $v0,0x0($s0)
 *   func_001283D0(D_0013CFA0, 0, 0x28);   ; memset the 10 words
 *   D_0013A07C = 0;                       ; reset the counter
 *
 * The memset argument re-materialises the address from the $s2 high half
 * (`addiu $a0,$s2,%lo(D_0013CFA0)`), i.e. the source names the table again
 * instead of reusing the loop pointer; D_0013A07C is a gp-relative scalar.
 * MATCH GUESS: cc=296 (saves 8 bytes apart; the 003F98 twin is 296) */
extern int D_0013CFA0[];        /* .bss 10-entry table: lui/%lo (non-small) */
extern int D_0013A07C;          /* gp-relative counter (small scalar) */

int func_001283D0(void *dst, int value, int size);

void func_00103F28(void) {
    int i;
    int *p = D_0013CFA0;

    for (i = 9; i >= 0; i--) {
        int f = *p++;

        if (f != 0)
            ((void (*)(void))f)();
    }
    func_001283D0(D_0013CFA0, 0, 0x28);
    D_0013A07C = 0;
}
