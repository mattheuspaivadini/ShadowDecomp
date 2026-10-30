/* GAMECORE.XFF @ 0x0D6BA8 (36 B) - is_safety_camera_default_angle
 * Evidence: `jal GAMEUTIL_get_cur_status_status_manager`, `xori $v0,$v0,1`,
 * `sltu $v0,$zero,$v0`.
 * UNCONFIRMED: GAMEUTIL_get_cur_status_status_manager return type
 
 */
int GAMEUTIL_get_cur_status_status_manager(void);

int is_safety_camera_default_angle(void) {
    return GAMEUTIL_get_cur_status_status_manager() != 1;
}
