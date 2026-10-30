/* GAMECORE.XFF @ 0x008E58 (12 B) - GAMEUTIL_get_game_camera_free_mode_angle_vel_ratio_int
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x234 - returns that object as `int`.
 */
extern int D_kernel_data_0234;

int GAMEUTIL_get_game_camera_free_mode_angle_vel_ratio_int(void) {
    return D_kernel_data_0234;
}
