/* KERNEL.XFF @ 0x012940 (12 B) - iosGetRootDC
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x554 - returns that object as `int`.
 */
extern int D_kernel_data_0554;

int iosGetRootDC(void) {
    return D_kernel_data_0554;
}
