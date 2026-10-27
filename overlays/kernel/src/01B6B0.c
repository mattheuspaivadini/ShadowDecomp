/* KERNEL.XFF @ 0x01B6B0 (12 B) - iosGetIVSyncMode
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x7e0 - returns that object as `int`.
 */
extern int D_kernel_data_07E0;

int iosGetIVSyncMode(void) {
    return D_kernel_data_07E0;
}
