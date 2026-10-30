/* GAMECORE.XFF @ 0x01E920 (12 B) - resetAttackPower
 * Evidence: sw zero -> bss+0x4AE8
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_4AE8[];

void resetAttackPower(void) {
    D_kernel_bss_4AE8[0] = 0;
}
