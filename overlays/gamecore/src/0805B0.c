/* GAMECORE.XFF @ 0x0805B0 (60 B) - nico_setPlayerDemoAdditionClothCollisionFloorTable1
 * Evidence: `$v0 = 0x80AC0` (.text function pointer), then six stores into the
 * .data block: the pointer at +0x15F0 and +0x1610, zero at +0x15F4, +0x15F8,
 * +0x15FC and +0x1614. Each store gets its own `lui` base with the offset in
 * the `sw` immediate, which only happens when every target is a *distinct*
 * symbol: a single base plus constant offsets makes gcc CSE one register and
 * emit `sw off(base)` instead.
 * UNCONFIRMED: the target function at 0x80AC0, the `.data` symbol names and
 * the table layout (two 0x20-byte entries starting at +0x15F0).
 
 */
extern void func_00080AC0(void);
extern void *D_kernel_data_15F0;
extern int D_kernel_data_15F4;
extern int D_kernel_data_15F8;
extern int D_kernel_data_15FC;
extern void *D_kernel_data_1610;
extern int D_kernel_data_1614;

void nico_setPlayerDemoAdditionClothCollisionFloorTable1(void) {
    D_kernel_data_15F0 = (void *)func_00080AC0;
    D_kernel_data_15F4 = 0;
    D_kernel_data_15F8 = 0;
    D_kernel_data_15FC = 0;
    D_kernel_data_1610 = (void *)func_00080AC0;
    D_kernel_data_1614 = 0;
}
