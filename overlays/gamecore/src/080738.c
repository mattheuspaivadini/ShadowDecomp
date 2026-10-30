/* GAMECORE.XFF @ 0x080738 (60 B) - nico_setPlayerDemoAdditionClothCollisionHomeBaseFloor
 * Evidence: like 0805B0 with `$v0 = 0x813B0`, but +0x15F8 also receives the
 * function pointer (`sw $v0, 0x15F8($a2)`).
 * UNCONFIRMED: the target function at 0x813B0 and the `.data` symbol names.
 
 */
extern void func_000813B0(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern void *D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern void *D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionHomeBaseFloor(void) {
    D_kernel_data_15F0 = (void *)func_000813B0;
    D_kernel_data_15F4 = 0;
    D_kernel_data_15F8 = (void *)func_000813B0;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = (void *)func_000813B0;
    D_kernel_data_1614 = 0;
}
