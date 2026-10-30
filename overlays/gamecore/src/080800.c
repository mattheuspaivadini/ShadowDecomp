/* GAMECORE.XFF @ 0x080800 (60 B) - nico_setPlayerDemoAdditionClothCollisionRightHand
 * Evidence: `$v0 = 0x81638`, then stores +0x15F0 = pointer, +0x15F4 = `$a0`
 * (the incoming argument), and zero at +0x15F8, +0x15FC, +0x1610, +0x1614.
 * Unlike the 0805B0 family the second entry's +0x1610 slot is cleared instead
 * of receiving the pointer. Six separate `lui` bases, so the targets are
 * distinct `.data` symbols.
 * UNCONFIRMED: the target function at 0x81638, the argument's meaning and the
 * `.data` symbol names.
 
 */
extern void func_00081638(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern int D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern int D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionRightHand(int arg) {
    D_kernel_data_15F0 = (void *)func_00081638;
    D_kernel_data_15F4 = arg;
    D_kernel_data_15F8 = 0;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = 0;
    D_kernel_data_1614 = 0;
}
