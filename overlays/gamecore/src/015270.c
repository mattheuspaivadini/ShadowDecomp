/* GAMECORE.XFF @ 0x015270 (24 B) - _gameIWorkSet
 * Evidence: ptr at .data+0x784; ptr[a0] = a1
 * UNCONFIRMED: none
 */
extern int *D_kernel_data_0784;

void _gameIWorkSet(int i, int v) {
    D_kernel_data_0784[i] = v;
}
