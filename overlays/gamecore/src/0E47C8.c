/* GAMECORE.XFF @ 0x0E47C8 (12 B) - get_debug_camera_view_angle
 * Evidence: ops lwc1; data <.data>+0x1E60
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern float D_kernel_data_1E60;
float get_debug_camera_view_angle(void) {
    return D_kernel_data_1E60;
}
