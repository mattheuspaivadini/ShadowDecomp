/* GAMECORE.XFF @ 0x107C00 (12 B) - chkGazeTool
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x1fc0 - returns that object as `int`.
 */
extern int D_kernel_data_1FC0;

int chkGazeTool(void) {
    return D_kernel_data_1FC0;
}
