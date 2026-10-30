/* GAMECORE.XFF @ 0x02CEA8 (12 B) - deleteWorldLayout
 * Evidence: sw zero -> .data+0xFD4
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0FD4[];

void deleteWorldLayout(void) {
    D_kernel_data_0FD4[0] = 0;
}
