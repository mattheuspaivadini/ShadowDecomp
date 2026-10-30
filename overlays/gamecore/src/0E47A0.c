/* GAMECORE.XFF @ 0x0E47A0 (40 B) - update_debug_camera_yaw_pitch
 * Evidence: `$a2 = $a0`, `$a1 = .data+0x1DE4`, `$a0 = .data+0x1DE0`, tail `j
 * GAMEUTIL_get_yaw_pitch_by_direction`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
extern float D_kernel_data_1DE0;
extern float D_kernel_data_1DE4;

void GAMEUTIL_get_yaw_pitch_by_direction(float *yaw, float *pitch, void *dir);

void update_debug_camera_yaw_pitch(void *dir) {
    GAMEUTIL_get_yaw_pitch_by_direction(&D_kernel_data_1DE0, &D_kernel_data_1DE4, dir);
}
