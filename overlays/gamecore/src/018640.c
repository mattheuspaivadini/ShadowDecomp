/* GAMECORE.XFF @ 0x018640 (16 B) - gameflowGameOver
 * Evidence: sw 1 -> bss+0xD50
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0D50[];

void gameflowGameOver(void) {
    D_kernel_bss_0D50[0] = 1;
}
