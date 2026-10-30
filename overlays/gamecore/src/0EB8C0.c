/* GAMECORE.XFF @ 0x0EB8C0 (44 B) - is_lws_fixed_point_mode
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls get_fixed_point_type_camera_lws_animation, j <.text>; frame
 
 */
/* UNCONFIRMED: tail-calls the shared LWS mode test at 0x0EB898 (outside this
 * work list, hence the offset stem).
 */
int get_fixed_point_type_camera_lws_animation(void);
int func_0EB898(char *p, int type);

int is_lws_fixed_point_mode(char *p) {
    return func_0EB898(p, get_fixed_point_type_camera_lws_animation());
}
