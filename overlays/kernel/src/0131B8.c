/* KERNEL.XFF @ 0x0131B8 (48 B) - iosCreateIVArbitrationSema
 * Evidence: iosCreateSema(0, 1, 0) stored through `lui/addiu` + offset 0 (volatile) at .bss+0x1EAD0. UNCONFIRMED: name.
 */
extern volatile int D_kernel_bss_1EAD0;
int iosCreateSema(int init, int max, int attr);

void iosCreateIVArbitrationSema(void) {
    D_kernel_bss_1EAD0 = iosCreateSema(0, 1, 0);
}
