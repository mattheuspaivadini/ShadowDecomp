/* GAMECORE.XFF @ 0x0DA8A0 (60 B) - constructor_camera_target_approach
 * Evidence: `jal GAMEUTIL_reset_status_manager` with `$a1 = 0`, `jal GAMEUTIL_constructor_position_filter` with
 * `$a0 = $s0+0x10`, `sw $zero -> +0x40`, tail `j CAM_init_aim_angle_rot` with `$a0 = +0x44, $a1 = 1`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void GAMEUTIL_reset_status_manager(void *p, int status);
void GAMEUTIL_constructor_position_filter(void *p);
void CAM_init_aim_angle_rot(void *p, int flag);

void constructor_camera_target_approach(char *p) {
    GAMEUTIL_reset_status_manager(p, 0);
    GAMEUTIL_constructor_position_filter(p + 0x10);
    *(int *)(p + 0x40) = 0;
    CAM_init_aim_angle_rot(p + 0x44, 1);
}
