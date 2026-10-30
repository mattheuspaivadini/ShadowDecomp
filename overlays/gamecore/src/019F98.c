/* GAMECORE.XFF @ 0x019F98 (20 B) - gstatBootMcSetExistNicoData
 * Evidence: two lui: .data+0x9E8=a0, .data+0x9EC=a1
 * UNCONFIRMED: none
 */
extern int D_kernel_data_09E8[];
extern int D_kernel_data_09EC[];

void gstatBootMcSetExistNicoData(int a, int b) {
    D_kernel_data_09E8[0] = a;
    D_kernel_data_09EC[0] = b;
}
