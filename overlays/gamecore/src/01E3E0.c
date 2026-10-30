/* GAMECORE.XFF @ 0x01E3E0 (12 B) - getPlayerHp
 * Evidence: lwc1 .bss+0x4AE4
 * UNCONFIRMED: none
 */
extern float D_kernel_bss_4AE4[];

float getPlayerHp(void) {
    return D_kernel_bss_4AE4[0];
}
