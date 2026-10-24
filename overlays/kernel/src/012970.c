/* KERNEL.XFF @ 0x012970 (12 B) - iosGetCurrentDC
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x550 - returns that object as `int`.
 */
extern int D_kernel_data_0550;

int iosGetCurrentDC(void) {
    return D_kernel_data_0550;
}
