/* GAMECORE.XFF @ 0x01C708 (20 B) - gcCheckStageLoadFinish
 * Evidence: nor+sltiu 1: .data+0xA14 == -1
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0A14[];

int gcCheckStageLoadFinish(void) {
    return D_kernel_data_0A14[0] == -1;
}
