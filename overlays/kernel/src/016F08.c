/* KERNEL.XFF @ 0x016F08 (56 B) - iFinish
 * Evidence: calls the hook at .data+0x628 when non-NULL, then sets the volatile flag at .data+0x610 to 1. UNCONFIRMED: names.
 */
extern void (*D_kernel_data_0628)(void);
extern volatile int D_kernel_data_0610;
void iFinish(void) {
    if (D_kernel_data_0628 != 0) {
        D_kernel_data_0628();
    }
    D_kernel_data_0610 = 1;
}
