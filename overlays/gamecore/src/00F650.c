/* GAMECORE.XFF @ 0x00F650 (28 B) - backStageInit
 * Evidence: sw -1 to .bss+0x38+{0x48,0,0x24}
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0038[];

void backStageInit(void) {
    D_kernel_bss_0038[0] = -1;
    D_kernel_bss_0038[9] = -1;
    D_kernel_bss_0038[18] = -1;
}
