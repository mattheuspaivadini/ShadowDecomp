/* GAMECORE.XFF @ 0x0806F8 (60 B) - nico_setPlayerDemoAdditionClothCollisionFloorTable
 * Evidence: identical to 0805B0 with `$v0 = 0x81210`.
 * UNCONFIRMED: the target function at 0x81210 and the `.data` symbol names.
 
 */
extern void func_00081210(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern int D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern void *D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionFloorTable(void) {
    D_kernel_data_15F0 = (void *)func_00081210;
    D_kernel_data_15F4 = 0;
    D_kernel_data_15F8 = 0;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = (void *)func_00081210;
    D_kernel_data_1614 = 0;
}
