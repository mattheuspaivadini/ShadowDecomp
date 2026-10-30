/* GAMECORE.XFF @ 0x01D7F8 (24 B) - opflowOp2Start
 * Evidence: ori 2 on .data+0xA50
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0A50[];

void opflowOp2Start(void) {
    D_kernel_data_0A50[0] |= 2;
}
