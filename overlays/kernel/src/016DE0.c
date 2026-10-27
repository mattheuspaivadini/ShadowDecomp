/* KERNEL.XFF @ 0x016DE0 (16 B) - iosSetVSchedulerFunc
 * Shape `store-arg-ret` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `addiu $v0,$zero,1` + `jr $ra` + delay `sw $a0,lo(...)` - stores the argument in .data+0x634 and returns 1.
 */
extern int D_kernel_data_0634;

int iosSetVSchedulerFunc(int v) {
    D_kernel_data_0634 = v;
    return 1;
}
