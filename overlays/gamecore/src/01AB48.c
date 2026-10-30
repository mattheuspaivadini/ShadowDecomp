/* GAMECORE.XFF @ 0x01AB48 (28 B) - jumphokoraflowDemoEnd
 * Evidence: ori 2 on .data+0xA00; a0 -> +0xA04
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0A00[];

void jumphokoraflowDemoEnd(unsigned int v) {
    D_kernel_data_0A00[0] |= 2;
    D_kernel_data_0A00[1] = v;
}
