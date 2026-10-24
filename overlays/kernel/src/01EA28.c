/* KERNEL.XFF @ 0x01EA28 (12 B) - soundGetTickProcCnt
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xa24 - returns that object as `int`.
 */
extern int D_kernel_data_0A24;

int soundGetTickProcCnt(void) {
    return D_kernel_data_0A24;
}
