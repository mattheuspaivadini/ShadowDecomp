/* KERNEL.XFF @ 0x01F2D8 (36 B) - iosMouseSetCallBackFunc
 * Evidence: returns 0 unless .data+0xA34 (init flag) is set; then .data+0xA38 = func and returns 1. UNCONFIRMED: names.
 */
extern int D_kernel_data_0A34;
extern void *D_kernel_data_0A38;

int iosMouseSetCallBackFunc(void *func) {
    if (D_kernel_data_0A34 == 0) {
        return 0;
    }
    D_kernel_data_0A38 = func;
    return 1;
}
