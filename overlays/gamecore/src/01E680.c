/* GAMECORE.XFF @ 0x01E680 (12 B) - getPlayerGrip
 * Evidence: lwc1 .bss+0x4AE0
 * UNCONFIRMED: none
 */
extern float D_kernel_bss_4AE0[];

float getPlayerGrip(void) {
    return D_kernel_bss_4AE0[0];
}
