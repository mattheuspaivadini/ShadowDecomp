/* KERNEL.XFF @ 0x01EA18 (12 B) - setPcmTickProcFunc
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x8d40c.
 */
extern int D_kernel_bss_D40C;

void setPcmTickProcFunc(int a0) {
    D_kernel_bss_D40C = a0;
}
