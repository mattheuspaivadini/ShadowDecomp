/* GAMECORE.XFF @ 0x01D840 (20 B) - opflowChkTitleDemoStart
 * Evidence: srl 4, andi 1 on .data+0xA50
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0A50[];

int opflowChkTitleDemoStart(void) {
    return (D_kernel_data_0A50[0] >> 4) & 1;
}
