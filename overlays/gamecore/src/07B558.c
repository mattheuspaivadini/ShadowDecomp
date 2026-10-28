/* GAMECORE.XFF @ 0x07B558 (12 B) - getPlayerLastParentObj
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x15d8 - returns that object as `int`.
 */
extern int D_kernel_data_15D8;

int getPlayerLastParentObj(void) {
    return D_kernel_data_15D8;
}
