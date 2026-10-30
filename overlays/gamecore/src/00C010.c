/* GAMECORE.XFF @ 0x00C010 (24 B) - RestoreDefaultGameAnimeTimeScaleRatio
 * Evidence: 0x3F666666 (0.9f) stored to .data+0x5F4
 * UNCONFIRMED: none
 */
extern float D_kernel_data_05F4[];

void RestoreDefaultGameAnimeTimeScaleRatio(void) {
    D_kernel_data_05F4[0] = 0.9f;
}
