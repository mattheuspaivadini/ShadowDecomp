/* KERNEL.XFF @ 0x01EF88 (36 B) - iosKeybdSetCallBackFunc
 * Evidence: returns 0 unless .data+0xA2C (init flag) is set; then .data+0xA30 = func and returns 1. UNCONFIRMED: names.
 */
extern int D_kernel_data_0A2C;
extern void *D_kernel_data_0A30;

int iosKeybdSetCallBackFunc(void *func) {
    if (D_kernel_data_0A2C == 0) {
        return 0;
    }
    D_kernel_data_0A30 = func;
    return 1;
}
