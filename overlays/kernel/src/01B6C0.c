/* KERNEL.XFF @ 0x01B6C0 (16 B) - vschedSetNextFrameForceGarbage
 * Evidence: .data+0x7DC = 1. UNCONFIRMED: name.
 */
extern int D_kernel_data_07DC;

void vschedSetNextFrameForceGarbage(void) {
    D_kernel_data_07DC = 1;
}
