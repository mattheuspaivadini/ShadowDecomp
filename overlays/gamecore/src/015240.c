/* GAMECORE.XFF @ 0x015240 (24 B) - _gameWorkSet
 * Evidence: bss+0x420[a0] = a1
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0420[];

void _gameWorkSet(int i, int v) {
    D_kernel_bss_0420[i] = v;
}
