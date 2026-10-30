/* GAMECORE.XFF @ 0x11C510 (12 B) - setConditionResultBoss
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x21f50.
 */
extern int D_kernel_bss_21F50;

void setConditionResultBoss(int a0) {
    D_kernel_bss_21F50 = a0;
}
