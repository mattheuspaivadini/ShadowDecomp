/* GAMECORE.XFF @ 0x0807C0 (60 B) - nico_setPlayerDemoAdditionClothCollisionEvisFloor
 * Evidence: like 080738 with `$v0 = 0x81608`.
 * UNCONFIRMED: the target function at 0x81608 and the `.data` symbol names.
 
 */
extern void func_00081608(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern void *D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern void *D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionEvisFloor(void) {
    D_kernel_data_15F0 = (void *)func_00081608;
    D_kernel_data_15F4 = 0;
    D_kernel_data_15F8 = (void *)func_00081608;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = (void *)func_00081608;
    D_kernel_data_1614 = 0;
}
