/* GAMECORE.XFF @ 0x0BC460 (12 B) - getNowExecEventScriptObj
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x171c - returns that object as `int`.
 */
extern int D_kernel_data_171C;

int getNowExecEventScriptObj(void) {
    return D_kernel_data_171C;
}
