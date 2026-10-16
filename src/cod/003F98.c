/* asm/cod/003F98.s -> func_00103F98 @ 0x00103F98 (0x5C bytes, 23 insns)
 *
 * Append a0 to the 10-entry table D_0013CFA0 when the counter D_0013A07C is
 * full (== 10): report through func_00102CF8(D_00136D30) first and reset the
 * counter, then store and post-increment:
 *   if (D_0013A07C == 10) { func_00102CF8(D_00136D30); D_0013A07C = 0; }
 *   D_0013CFA0[D_0013A07C++] = a0;
 * D_0013A07C is addressed %gp_rel (a small scalar); the table is non-small, so
 * the store is `lui $at,%hi; addu $at,$at,$a0` + `sw $s0,%lo($at)` with the
 * index scaled by 4, and the counter is written back after the store (the
 * post-increment). $s0 holds a0 across the call; $s0/$ra are 8 bytes apart.
 * MATCH GUESS: cc=296 */
extern int D_0013A07C;        /* .sbss/.sdata: gp-relative (small scalar) */
extern char D_00136D30[];     /* lui/%lo (non-small) - the message */
extern int D_0013CFA0[];      /* lui/%lo (non-small) - the 10-entry table */
int LoaderSysPrintf(char *fmt, ...);

void loaderSetResetCallback(int a0) {
    if (D_0013A07C == 10) {
        LoaderSysPrintf(D_00136D30);
        D_0013A07C = 0;
    }
    D_0013CFA0[D_0013A07C++] = a0;
}
