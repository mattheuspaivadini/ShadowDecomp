/* GAMECORE.XFF @ 0x0150E8 (24 B) - _optionWorkSet
 * Evidence: bss+0x348[a0] = a1
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0348[];

void _optionWorkSet(int i, int v) {
    D_kernel_bss_0348[i] = v;
}
