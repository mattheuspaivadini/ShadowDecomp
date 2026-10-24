/* GAMECORE.XFF @ 0x0DBBD8 (8 B) - end_get_yaw_pitch_camera_target_visible_angle_manager
 * Evidence: `jr $ra` with `ac8003d0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void end_get_yaw_pitch_camera_target_visible_angle_manager(unsigned char *p) {
    *(int *)(p + 0x3d0) = 0;
}
