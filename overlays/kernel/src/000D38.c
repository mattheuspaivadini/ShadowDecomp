/* KERNEL.XFF @ 0x000D38 (120 B) - iosDI
 * Evidence: DIntr(); the nesting counter at .data+0xA4 must be 0 when interrupts were on, and positive when they were already off; otherwise iosJumpRecoverPoint(.rodata+0xE8 / +0x100, counter); then ++counter. UNCONFIRMED: counter name.
 */
extern int D_kernel_data_00A4;
extern char D_kernel_rodata_00E8[];
extern char D_kernel_rodata_0100[];
int DIntr(void);
void iosJumpRecoverPoint(const char *fmt, ...);

void iosDI(void) {
    if (DIntr()) {
        if (D_kernel_data_00A4 != 0) {
            iosJumpRecoverPoint(D_kernel_rodata_00E8, D_kernel_data_00A4);
        }
    } else {
        if (D_kernel_data_00A4 <= 0) {
            iosJumpRecoverPoint(D_kernel_rodata_0100, D_kernel_data_00A4);
        }
    }
    D_kernel_data_00A4++;
}
