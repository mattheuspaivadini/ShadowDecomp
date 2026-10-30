/* GAMECORE.XFF @ 0x0139E8 (24 B) - endingflowDemoEnd
 * Evidence: ori 1 on .data+0x768
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0768[];

void endingflowDemoEnd(void) {
    D_kernel_data_0768[0] |= 1;
}
