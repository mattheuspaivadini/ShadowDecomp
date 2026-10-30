/* GAMECORE.XFF @ 0x01D858 (24 B) - opflowTitleDmoeEnd
 * Evidence: ori 0x20 on .data+0xA50
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0A50[];

void opflowTitleDmoeEnd(void) {
    D_kernel_data_0A50[0] |= 0x20;
}
