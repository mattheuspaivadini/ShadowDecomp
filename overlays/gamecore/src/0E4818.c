/* GAMECORE.XFF @ 0x0E4818 (20 B) - set_debug_camera_move_diff
 * Evidence: ops swc1; data <.data>+0x1DE8, <.data>+0x1DEC
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern float D_kernel_data_1DE8;
extern float D_kernel_data_1DEC;

void set_debug_camera_move_diff(float a, float b) {
    D_kernel_data_1DE8 = a;
    D_kernel_data_1DEC = b;
}
