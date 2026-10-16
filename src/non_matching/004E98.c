/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 11 [cc=296, default].
 * record pointer + XOR checksum.
 * The original .s stays in the build (asm/cod/004E98.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/004E98.s -> func_00104E98 @ 0x00104E98 (0x5C bytes, 23 insns)
 *
 * Device record 0 of the D_0013D840 table lives at D_0013D840 + 0x100; fetch
 * its status bytes and return them complemented:
 *   p = D_0013D840 + 0x104;                    ($s1 = $s0 + 0x104)
 *   r = func_00115210(*(int *)(D_0013D840+0x11C), p);
 *   if (r < 0) return 0;
 *   return ((unsigned)p[0] << 8 | D_0013D840[0x105]) ^ 0xFFFF;
 * The base is built once into $s0 (lui + addiu %lo(D_0013D840) - no folded
 * addend, so the source adds the byte offsets) and the byte pointer $s1 is live
 * across the call (hence callee-saved). The low byte arrives in the delay slot
 * of `bgezl` (only the r >= 0 path needs it). $s0/$s1/$ra are 8 bytes apart.
 * MATCH GUESS: cc=296 */
extern char D_0013D840[];   /* .bss 0x0013D840: lui/%lo (non-small) */
int scePad2Read(int a0, unsigned char *a1);

int padSysReadForLoader(void) {
    unsigned char *p = (unsigned char *)(D_0013D840 + 0x104);
    int r;

    r = scePad2Read(*(int *)(D_0013D840 + 0x11C), p);
    if (r < 0)
        return 0;
    return ((unsigned int)p[0] << 8 | D_0013D840[0x105]) ^ 0xFFFF;
}
