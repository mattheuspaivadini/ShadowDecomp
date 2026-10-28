/* GAMECORE.XFF @ 0x008DE8 (12 B) - GAMEUTIL_set_game_camera_free_mode_reverse_cntrlLR
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x22c.
 */
extern int D_kernel_data_022C;

void GAMEUTIL_set_game_camera_free_mode_reverse_cntrlLR(int a0) {
    D_kernel_data_022C = a0;
}
