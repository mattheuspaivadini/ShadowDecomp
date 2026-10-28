/* GAMECORE.XFF @ 0x0EB838 (12 B) - getBossInterestKey
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x1e7c - returns that object as `int`.
 */
extern int D_kernel_data_1E7C;

int getBossInterestKey(void) {
    return D_kernel_data_1E7C;
}
