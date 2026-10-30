/* GAMECORE.XFF @ 0x0185B0 (40 B) - gameflowSetPauseEnable
 * Evidence: no loads/stores; data <.data>+0x244307d4
 */
/* variant D: negated ternary, single store */
extern int D_kernel_data_07D4[];

void gameflowSetPauseEnable(int enable) {
    D_kernel_data_07D4[0] = !enable ? D_kernel_data_07D4[0] + 1
                                    : D_kernel_data_07D4[0] - 1;
}
