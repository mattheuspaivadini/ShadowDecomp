/* KERNEL.XFF @ 0x01B400 (20 B) - getVIntrCnt
 * Evidence: volatile load of .data+0x7D4 (lui/addiu + 0, nop slot). UNCONFIRMED: name.
 */
extern volatile int D_kernel_data_07D4;

int getVIntrCnt(void) {
    return D_kernel_data_07D4;
}
