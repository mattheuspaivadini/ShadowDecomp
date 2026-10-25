/* KERNEL.XFF @ 0x000DB0 (112 B) - iosEI
 * Evidence: --counter (.data+0xA4); at 0 EIntr() and a non-zero result (interrupts already on) is fatal (.rodata+0x118); a negative count is fatal (.rodata+0x148); returns the counter (reloaded).
 */
extern int D_kernel_data_00A4;
extern char D_kernel_rodata_0118[];
extern char D_kernel_rodata_0148[];
int EIntr(void);
void iosJumpRecoverPoint(const char *fmt, ...);

int iosEI(void) {
    if (--D_kernel_data_00A4 == 0) {
        if (EIntr()) {
            iosJumpRecoverPoint(D_kernel_rodata_0118);
        }
    } else if (D_kernel_data_00A4 < 0) {
        iosJumpRecoverPoint(D_kernel_rodata_0148);
    }
    return D_kernel_data_00A4;
}
