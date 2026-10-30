/* GAMECORE.XFF @ 0x121000 (20 B) - setScrDemoMangerFinishCallback
 * Evidence: ops sw; data <.data>+0x2000, <.data>+0x2004
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_data_2000;
extern int D_kernel_data_2004;

void setScrDemoMangerFinishCallback(int a, int b) {
    D_kernel_data_2000 = a;
    D_kernel_data_2004 = b;
}
