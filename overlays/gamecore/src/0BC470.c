/* GAMECORE.XFF @ 0x0BC470 (20 B) - setLoadingCheckFunc
 * Evidence: ops sw; data <.data>+0x1724, <.data>+0x1720
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_data_1724;
extern int D_kernel_data_1720;

void setLoadingCheckFunc(int a, int b) {
    D_kernel_data_1724 = a;
    D_kernel_data_1720 = b;
}
