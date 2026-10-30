/* GAMECORE.XFF @ 0x0DA980 (24 B) - reset_pitch_rot_cntrl_camera_target_approach
 * Evidence: ops ld sd; calls j CAM_reset_aim_angle_rot; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void CAM_reset_aim_angle_rot(char *p);
void reset_pitch_rot_cntrl_camera_target_approach(char *p) {
    CAM_reset_aim_angle_rot(p + 0x44);
}
