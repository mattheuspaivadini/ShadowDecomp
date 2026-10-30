/* GAMECORE.XFF @ 0x015258 (24 B) - _gameFWorkSet
 * Evidence: ptr at .data+0x780; ptr[a0] = f12
 * UNCONFIRMED: none
 */
extern float *D_kernel_data_0780;

void _gameFWorkSet(int i, float v) {
    D_kernel_data_0780[i] = v;
}
