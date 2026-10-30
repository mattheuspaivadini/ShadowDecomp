/* GAMECORE.XFF @ 0x080840 (60 B) - nico_setPlayerDemoAdditionClothCollisionRightHandY
 * Evidence: identical to 080800 with `$v0 = 0x817C8`.
 * UNCONFIRMED: the target function at 0x817C8 and the `.data` symbol names.
 
 */
extern void func_000817C8(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern int D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern int D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionRightHandY(int arg) {
    D_kernel_data_15F0 = (void *)func_000817C8;
    D_kernel_data_15F4 = arg;
    D_kernel_data_15F8 = 0;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = 0;
    D_kernel_data_1614 = 0;
}
