/* KERNEL.XFF @ 0x01ECE8 (28 B) - iosSignalIopSema
 * Evidence: sibling SignalSema(.bss+0x7D410).
 */
extern int D_kernel_bss_7D410;
int SignalSema(int sema);

void iosSignalIopSema(void) {
    SignalSema(D_kernel_bss_7D410);
}
