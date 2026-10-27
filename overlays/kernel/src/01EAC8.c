/* KERNEL.XFF @ 0x01EAC8 (20 B) - getSoundMode
 * Evidence: returns .data+0xA20 == 1.
 */
extern int D_kernel_data_0A20;

int getSoundMode(void) {
    return D_kernel_data_0A20 == 1;
}
