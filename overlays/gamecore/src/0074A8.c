/* GAMECORE.XFF @ 0x0074A8 (12 B) - DebugGetMutekiMode
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x20 - returns that object as `int`.
 */
extern int D_kernel_data_0020;

int DebugGetMutekiMode(void) {
    return D_kernel_data_0020;
}
