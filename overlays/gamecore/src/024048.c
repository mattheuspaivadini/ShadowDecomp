/* GAMECORE.XFF @ 0x024048 (12 B) - GetLoadAreaGroupData
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xa60 - returns that object as `int`.
 */
extern int D_kernel_data_0A60;

int GetLoadAreaGroupData(void) {
    return D_kernel_data_0A60;
}
