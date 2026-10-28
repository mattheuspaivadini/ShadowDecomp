/* GAMECORE.XFF @ 0x008DF8 (12 B) - GAMEUTIL_get_game_camera_free_mode_reverse_cntrlLR_int
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x22c - returns that object as `int`.
 */
extern int D_kernel_data_022C;

int GAMEUTIL_get_game_camera_free_mode_reverse_cntrlLR_int(void) {
    return D_kernel_data_022C;
}
