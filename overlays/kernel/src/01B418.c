/* KERNEL.XFF @ 0x01B418 (24 B) - setVIntrBaseTime
 * Evidence: t[0] = volatile .data+0x7D4 (the vsync counter of getVIntrCnt), t[1] = 0. UNCONFIRMED: struct type of t.
 */
extern volatile int D_kernel_data_07D4;

void setVIntrBaseTime(int *t) {
    t[0] = D_kernel_data_07D4;
    t[1] = 0;
}
