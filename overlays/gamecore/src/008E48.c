/* GAMECORE.XFF @ 0x008E48 (12 B) - GAMEUTIL_set_game_camera_free_mode_angle_vel_ratio
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x234.
 */
extern int D_kernel_data_0234;

void GAMEUTIL_set_game_camera_free_mode_angle_vel_ratio(int a0) {
    D_kernel_data_0234 = a0;
}
