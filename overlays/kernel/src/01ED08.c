/* KERNEL.XFF @ 0x01ED08 (44 B) - InitIopDev
 * Evidence: .bss+0x7D410 = iosCreateSema(1, 1, 0).
 */
extern int D_kernel_bss_7D410;
int iosCreateSema(int init, int max, int attr);

void InitIopDev(void) {
    D_kernel_bss_7D410 = iosCreateSema(1, 1, 0);
}
