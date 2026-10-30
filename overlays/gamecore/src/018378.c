/* GAMECORE.XFF @ 0x018378 (12 B) - gameflowSelectGameoverMenu
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xd54.
 */
extern int D_kernel_bss_0D54;

void gameflowSelectGameoverMenu(int a0) {
    D_kernel_bss_0D54 = a0;
}
