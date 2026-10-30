/* GAMECORE.XFF @ 0x015D68 (24 B) - getClearGameHotStartFlag
 * Evidence: ld bss+0xC58; dsll 24; dsra32 0; andi 1
 * UNCONFIRMED: bitfield shape
 */
extern long D_kernel_bss_0C58[];

int getClearGameHotStartFlag(void) {
    return (int)(D_kernel_bss_0C58[0] >> 8) & 1;
}
