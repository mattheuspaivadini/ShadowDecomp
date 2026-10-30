/* GAMECORE.XFF @ 0x0F7DD0 (12 B) - setBossPathColiGroup
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x2c8c0.
 */
extern int D_kernel_bss_2C8C0;

void setBossPathColiGroup(int a0) {
    D_kernel_bss_2C8C0 = a0;
}
