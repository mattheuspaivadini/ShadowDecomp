/* GAMECORE.XFF @ 0x01AB68 (28 B) - jumphokoraGetDemoInfo
 * Evidence: two lui: bss+0x4AA0 -> *a0, bss+0x4AA4 -> *a1
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_4AA0[];
extern int D_kernel_bss_4AA4[];

void jumphokoraGetDemoInfo(int *a, int *b) {
    *a = D_kernel_bss_4AA0[0];
    *b = D_kernel_bss_4AA4[0];
}
