/* GAMECORE.XFF @ 0x0242D0 (32 B) - PauseSeamlessStageManager
 * Evidence: a0 -> .data+0xA94; if !a0 .data+0xA7C = 1
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0A94[];
extern int D_kernel_data_0A7C[];

void PauseSeamlessStageManager(int v) {
    D_kernel_data_0A94[0] = v;
    if (v == 0)
        D_kernel_data_0A7C[0] = 1;
}
