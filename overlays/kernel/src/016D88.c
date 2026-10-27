/* KERNEL.XFF @ 0x016D88 (16 B) - iosSetIStartFunc
 * Shape `store-arg-ret` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `addiu $v0,$zero,1` + `jr $ra` + delay `sw $a0,lo(...)` - stores the argument in .data+0x624 and returns 1.
 */
extern int D_kernel_data_0624;

int iosSetIStartFunc(int v) {
    D_kernel_data_0624 = v;
    return 1;
}
