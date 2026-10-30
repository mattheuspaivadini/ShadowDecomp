/* GAMECORE.XFF @ 0x0152D0 (24 B) - _gameIWorkChk
 * Evidence: ptr at .data+0x784; return ptr[a0]
 * UNCONFIRMED: none
 */
extern int *D_kernel_data_0784;

int _gameIWorkChk(int i) {
    return D_kernel_data_0784[i];
}
