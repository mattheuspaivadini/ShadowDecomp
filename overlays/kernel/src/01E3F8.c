/* KERNEL.XFF @ 0x01E3F8 (36 B) - sndSepPauseAll
 * Evidence: .data+0xA1C = 1 when pausing, else 0 (two stores). UNCONFIRMED: name.
 */
extern int D_kernel_data_0A1C;

void sndSepPauseAll(int pause) {
    if (pause) {
        D_kernel_data_0A1C = 1;
    } else {
        D_kernel_data_0A1C = 0;
    }
}
