/* GAMECORE.XFF @ 0x0F7DE0 (12 B) - setHorsePathColiGroup
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x2c8c4.
 */
extern int D_kernel_bss_2C8C4;

void setHorsePathColiGroup(int a0) {
    D_kernel_bss_2C8C4 = a0;
}
