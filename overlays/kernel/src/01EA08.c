/* KERNEL.XFF @ 0x01EA08 (12 B) - addAdpcmTickProcFunc
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x8d408.
 */
extern int D_kernel_bss_D408;

void addAdpcmTickProcFunc(int a0) {
    D_kernel_bss_D408 = a0;
}
