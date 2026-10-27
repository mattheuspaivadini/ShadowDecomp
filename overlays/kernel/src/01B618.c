/* KERNEL.XFF @ 0x01B618 (60 B) - ischedStop
 * Evidence: on the first nested stop clears bit 7 of INTC_MASK 0x10000010, then increments the volatile depth at .bss+0x791A0. UNCONFIRMED: names.
 */
extern volatile int D_kernel_bss_791A0;

void ischedStop(void) {
    if (D_kernel_bss_791A0 == 0) {
        *(volatile int *)0x10000010 &= ~0x80;
    }
    D_kernel_bss_791A0++;
}
