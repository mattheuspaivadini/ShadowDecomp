/* GAMECORE.XFF @ 0x0152B8 (24 B) - _gameFWorkChk
 * Evidence: ptr at .data+0x780; return ptr[a0]
 * UNCONFIRMED: none
 */
extern float *D_kernel_data_0780;

float _gameFWorkChk(int i) {
    return D_kernel_data_0780[i];
}
