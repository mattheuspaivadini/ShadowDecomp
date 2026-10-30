/* GAMECORE.XFF @ 0x00C038 (32 B) - setGameAnimeTimeScaleRatio
 * Evidence: f12 = .data+0x5F4, f13 = 0, sibling j .text+0xBF50
 * UNCONFIRMED: callee unnamed static
 */
extern float D_kernel_data_05F4[];
void func_0000BF50(float a, float b);

void setGameAnimeTimeScaleRatio(void) {
    func_0000BF50(D_kernel_data_05F4[0], 0.0f);
}
