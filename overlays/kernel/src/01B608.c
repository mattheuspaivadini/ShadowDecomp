/* KERNEL.XFF @ 0x01B608 (12 B) - iosGetISchedulerExecCnt
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x7e8 - returns that object as `int`.
 */
extern int D_kernel_data_07E8;

int iosGetISchedulerExecCnt(void) {
    return D_kernel_data_07E8;
}
