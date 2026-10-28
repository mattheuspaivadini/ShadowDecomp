/* GAMECORE.XFF @ 0x0EB848 (12 B) - getInterestKey
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x1e84 - returns that object as `int`.
 */
extern int D_kernel_data_1E84;

int getInterestKey(void) {
    return D_kernel_data_1E84;
}
