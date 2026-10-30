/* GAMECORE.XFF @ 0x0EB438 (52 B) - end_check_and_boot_boss_subjective_camera_lws_animation
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls <.text>, j end_camera_lws_animation_by_paramID; frame
 
 */
/* UNCONFIRMED: param id 0 means "no boss subjective animation running". */
int get_boss_subjective_camera_lws_animation_param(void);
void end_camera_lws_animation_by_paramID(int param);

void end_check_and_boot_boss_subjective_camera_lws_animation(void) {
    int param = get_boss_subjective_camera_lws_animation_param();
    if (param)
        end_camera_lws_animation_by_paramID(param);
}
