/* GAMECORE.XFF @ 0x00E948 (24 B) - activedemoflowDemoEnd
 * Evidence: ori 2 on .data+0x6D0
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_06D0[];

void activedemoflowDemoEnd(void) {
    D_kernel_data_06D0[0] |= 2;
}
