/* GAMECORE.XFF @ 0x00C028 (12 B) - SetDefaultGameAnimeTimeScaleRatio
 * Evidence: swc1 f12 -> .data+0x5F4
 * UNCONFIRMED: none
 */
extern float D_kernel_data_05F4[];

void SetDefaultGameAnimeTimeScaleRatio(float v) {
    D_kernel_data_05F4[0] = v;
}
