/* GAMECORE.XFF @ 0x015118 (24 B) - _optionWorkChk
 * Evidence: return bss+0x348[a0]
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0348[];

int _optionWorkChk(int i) {
    return D_kernel_bss_0348[i];
}
