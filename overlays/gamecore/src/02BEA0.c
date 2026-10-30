/* GAMECORE.XFF @ 0x02BEA0 (12 B) - GetWorldLayoutSheetSegHeader
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xfd4 - returns that object as `int`.
 */
extern int D_kernel_data_0FD4;

int GetWorldLayoutSheetSegHeader(void) {
    return D_kernel_data_0FD4;
}
