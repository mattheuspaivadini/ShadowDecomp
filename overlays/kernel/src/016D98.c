/* KERNEL.XFF @ 0x016D98 (16 B) - iosSetGpFinishFunc
 * Shape `store-arg-ret` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `addiu $v0,$zero,1` + `jr $ra` + delay `sw $a0,lo(...)` - stores the argument in .data+0x62c and returns 1.
 */
extern int D_kernel_data_062C;

int iosSetGpFinishFunc(int v) {
    D_kernel_data_062C = v;
    return 1;
}
