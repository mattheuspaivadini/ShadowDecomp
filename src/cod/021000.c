/* asm/cod/021000.s -> func_00121000 @ 0x00121000 (0x54 bytes, 21 insns)
 *
 * Clear-and-return a 0x80-byte .bss block:
 *
 *   func_00107020(D_00163CC0[0]);                       ; lw $a0,%lo(D_00163CC0)
 *   func_001318C0(&D_00165DC0, &D_00165DC0 + 0x7F);     ; (start, end-1)
 *   if (D_00165DC0[0] <= 0) D_00165DC0[2] = 0;          ; blezl $v0 -> sw $zero,0x8
 *   return (int)&D_00165DC0;                            ; daddu $v0,$s1,$zero
 *
 * The `blezl` puts the single store into the branch-delay slot, so it executes
 * only when the word at 0x0 is <= 0 (both paths continue at .L0012103C and the
 * function returns the block address in $s1).
 * MATCH GUESS: cc=296 (delay slots filled: the &D_00165DC0 high half and the
 * +0x7F sit in the jal shadow)
 */
extern int D_00163CC0[];   /* .bss 0x00163CC0, 8 bytes - array => lui/%lo */
extern int D_00165DC0[];   /* .bss 0x00165DC0, 0x80 bytes */

void WaitSema(int a0);
void SyncDCache(int a0, int a1);

int func_00121000(void) {
    WaitSema(D_00163CC0[0]);
    SyncDCache((int)D_00165DC0, (int)D_00165DC0 + 0x7F);
    if (D_00165DC0[0] <= 0)
        D_00165DC0[2] = 0;
    return (int)D_00165DC0;
}
