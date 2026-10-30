/* GAMECORE.XFF @ 0x04E798 (20 B) - effectGetDamageWork
 * Evidence: *a0 = bss+0x6BA0; return [bss+0x6BA0+0x2A8]
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_6BA0[];

int effectGetDamageWork(int **out) {
    *out = D_kernel_bss_6BA0;
    return D_kernel_bss_6BA0[0x2A8 / 4];
}
