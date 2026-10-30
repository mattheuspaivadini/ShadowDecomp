/* GAMECORE.XFF @ 0x013DA8 (12 B) - fadeCheck
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x770 - returns that object as `int`.
 */
extern int D_kernel_data_0770;

int fadeCheck(void) {
    return D_kernel_data_0770;
}
