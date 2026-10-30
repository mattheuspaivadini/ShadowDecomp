/* GAMECORE.XFF @ 0x0D1100 (24 B) - initPauseMenuMap
 * Evidence: ops sw; data <.data>+0x1AC0
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_data_1AC0[];

void initPauseMenuMap(void) {
    D_kernel_data_1AC0[0] = 0;
    D_kernel_data_1AC0[1] = 0;
    D_kernel_data_1AC0[2] = 0;
}
