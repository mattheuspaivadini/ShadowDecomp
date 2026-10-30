/* GAMECORE.XFF @ 0x024120 (16 B) - forceLoadSeamlessStage
 * Evidence: sw 1 -> .data+0xA7C
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0A7C[];

void forceLoadSeamlessStage(void) {
    D_kernel_data_0A7C[0] = 1;
}
