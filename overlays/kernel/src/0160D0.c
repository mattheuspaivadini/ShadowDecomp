/* KERNEL.XFF @ 0x0160D0 (16 B) - iosSetSyncNoReturnFunc
 * Shape `store-arg-ret` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `addiu $v0,$zero,1` + `jr $ra` + delay `sw $a0,lo(...)` - stores the argument in .data+0x5e0 and returns 1.
 */
extern int D_kernel_data_05E0;

int iosSetSyncNoReturnFunc(int v) {
    D_kernel_data_05E0 = v;
    return 1;
}
