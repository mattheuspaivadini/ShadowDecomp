/* KERNEL.XFF @ 0x01ECC8 (28 B) - iosWaitIopSema
 * Evidence: sibling WaitSema(.bss+0x7D410).
 */
extern int D_kernel_bss_7D410;
int WaitSema(int sema);

void iosWaitIopSema(void) {
    WaitSema(D_kernel_bss_7D410);
}
