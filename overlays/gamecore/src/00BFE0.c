/* GAMECORE.XFF @ 0x00BFE0 (12 B) - GetGameAnimeTimeScaleRatio
 * Evidence: lwc1 .data+0x5F4
 * UNCONFIRMED: none
 */
extern float D_kernel_data_05F4[];

float GetGameAnimeTimeScaleRatio(void) {
    return D_kernel_data_05F4[0];
}
