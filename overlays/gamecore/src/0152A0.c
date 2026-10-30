/* GAMECORE.XFF @ 0x0152A0 (24 B) - _gameWorkChk
 * Evidence: return bss+0x420[a0]
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_0420[];

int _gameWorkChk(int i) {
    return D_kernel_bss_0420[i];
}
