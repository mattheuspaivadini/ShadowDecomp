/* GAMECORE.XFF @ 0x0D1148 (36 B) - setLoadMapOffset
 * Evidence: four independent `lui` HI16/LO16 pairs, `swc1` to <.data>+0x1AE8/0x1AEC,
 * `sw` to <.data>+0x1AF0/0x1AF4 (image store order 1AE8,1AEC,1AF0,1AF4).
 * UNCONFIRMED: field meanings
 
 */
extern float D_kernel_data_1AE8[];
extern float D_kernel_data_1AEC[];
extern int D_kernel_data_1AF0[];
extern int D_kernel_data_1AF4[];

void setLoadMapOffset(float x, float y, int a, int b) {
    D_kernel_data_1AE8[0] = x;
    D_kernel_data_1AEC[0] = y;
    D_kernel_data_1AF0[0] = a;
    D_kernel_data_1AF4[0] = b;
}
