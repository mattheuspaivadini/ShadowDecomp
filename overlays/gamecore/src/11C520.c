/* GAMECORE.XFF @ 0x11C520 (12 B) - setConditionResultHorse
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x21f54.
 */
extern int D_kernel_bss_21F54;

void setConditionResultHorse(int a0) {
    D_kernel_bss_21F54 = a0;
}
