/* KERNEL.XFF @ 0x01B658 (56 B) - ischedRestart
 * Evidence: decrements the volatile depth at .bss+0x791A0 and, when it is 0 again (reloaded), sets bit 7 of INTC_MASK 0x10000010. UNCONFIRMED: names.
 */
extern volatile int D_kernel_bss_791A0;

void ischedRestart(void) {
    D_kernel_bss_791A0--;
    if (D_kernel_bss_791A0 == 0) {
        *(volatile int *)0x10000010 |= 0x80;
    }
}
