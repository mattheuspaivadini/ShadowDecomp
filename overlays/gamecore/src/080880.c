/* GAMECORE.XFF @ 0x080880 (60 B) - nico_setPlayerDemoAdditionClothCollisionHand
 * Evidence: identical to 080800 with `$v0 = 0x81B30`.
 * UNCONFIRMED: the target function at 0x81B30 and the `.data` symbol names.
 
 */
extern void func_00081B30(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern int D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern int D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionHand(int arg) {
    D_kernel_data_15F0 = (void *)func_00081B30;
    D_kernel_data_15F4 = arg;
    D_kernel_data_15F8 = 0;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = 0;
    D_kernel_data_1614 = 0;
}
