/* GAMECORE.XFF @ 0x01D7E0 (24 B) - opflowOp1End
 * Evidence: ori 0x11 on .data+0xA50
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0A50[];

void opflowOp1End(void) {
    D_kernel_data_0A50[0] |= 0x11;
}
