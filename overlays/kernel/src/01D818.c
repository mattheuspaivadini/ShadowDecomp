/* KERNEL.XFF @ 0x01D818 (12 B) - isysGetThisSubThread
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xa10 - returns that object as `int`.
 */
extern int D_kernel_data_0A10;

int isysGetThisSubThread(void) {
    return D_kernel_data_0A10;
}
