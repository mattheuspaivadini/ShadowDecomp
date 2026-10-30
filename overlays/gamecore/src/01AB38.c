/* GAMECORE.XFF @ 0x01AB38 (16 B) - jumphokoraflowDemoStart
 * Evidence: andi 1 on .data+0xA00
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0A00[];

int jumphokoraflowDemoStart(void) {
    return D_kernel_data_0A00[0] & 1;
}
