/* GAMECORE.XFF @ 0x015440 (16 B) - getGameHardMode
 * Evidence: bss+0xC7C != 0
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0C7C[];

int getGameHardMode(void) {
    return D_kernel_bss_0C7C[0] != 0;
}
