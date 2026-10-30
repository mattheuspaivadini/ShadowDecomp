/* GAMECORE.XFF @ 0x0808C0 (60 B) - nico_setPlayerDemoAdditionClothCollisionLeftHandY
 * Evidence: identical to 080800 with `$v0 = 0x81E28`.
 * UNCONFIRMED: the target function at 0x81E28 and the `.data` symbol names.
 
 */
extern void func_00081E28(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern int D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern int D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionLeftHandY(int arg) {
    D_kernel_data_15F0 = (void *)func_00081E28;
    D_kernel_data_15F4 = arg;
    D_kernel_data_15F8 = 0;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = 0;
    D_kernel_data_1614 = 0;
}
