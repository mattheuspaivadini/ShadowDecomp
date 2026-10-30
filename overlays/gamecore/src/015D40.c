/* GAMECORE.XFF @ 0x015D40 (40 B) - setClearGameHotStartFlag
 * Evidence: 64-bit read-modify-write of .bss+0xC58: `andi $a0, 1`,
 * `addiu $a1, -0x101` (the ~0x100 mask), `dsll $a0, 8`, `and`, `or`, `sd`.
 * UNCONFIRMED: the flag word meaning (bit 8 = clear-game hot start).
 
 */
extern long D_kernel_bss_0C58[];

void setClearGameHotStartFlag(int on) {
    D_kernel_bss_0C58[0] = (D_kernel_bss_0C58[0] & ~0x100L) | ((long)(on & 1) << 8);
}
