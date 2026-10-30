/* GAMECORE.XFF @ 0x0D1268 (20 B) - LoadWaitCancel
 * Evidence: ops sw; data <.data>+0x1B4C, <.data>+0x1B44
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_data_1B4C;
extern int D_kernel_data_1B44;

void LoadWaitCancel(int a) {
    D_kernel_data_1B4C = a;
    D_kernel_data_1B44 = 0;
}
