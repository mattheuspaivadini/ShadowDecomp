/* GAMECORE.XFF @ 0x00E970 (16 B) - chkActiveDemoStart
 * Evidence: andi 1 on .data+0x6D0
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_06D0[];

int chkActiveDemoStart(void) {
    return D_kernel_data_06D0[0] & 1;
}
