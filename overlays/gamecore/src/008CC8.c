/* GAMECORE.XFF @ 0x008CC8 (12 B) - GAMEUTIL_get_sight_on_reverse_cntrlLR_int
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x220 - returns that object as `int`.
 */
extern int D_kernel_data_0220;

int GAMEUTIL_get_sight_on_reverse_cntrlLR_int(void) {
    return D_kernel_data_0220;
}
