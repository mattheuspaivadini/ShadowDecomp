/* GAMECORE.XFF @ 0x015130 (24 B) - _optionWorkPtr
 * Evidence: return &bss+0x348[a0]
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0348[];

int *_optionWorkPtr(int i) {
    return &D_kernel_bss_0348[i];
}
