/* GAMECORE.XFF @ 0x008E18 (12 B) - GAMEUTIL_set_game_camera_free_mode_reverse_cntrlUD
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x230.
 */
extern int D_kernel_data_0230;

void GAMEUTIL_set_game_camera_free_mode_reverse_cntrlUD(int a0) {
    D_kernel_data_0230 = a0;
}
