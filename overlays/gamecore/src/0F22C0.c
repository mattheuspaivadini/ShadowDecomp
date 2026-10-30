/* GAMECORE.XFF @ 0x0F22C0 (28 B) - get_interp_time_game_camera_param_manager
 * Evidence: lwc1 0x20, compare with 0.0, else 0x670; needs -fno-schedule-insns
 * UNCONFIRMED: field names/types guessed from offsets
 */
float get_interp_time_game_camera_param_manager(char *p) {
    float t = *(float *)(p + 0x20);
    return 0.0f > t ? *(float *)(p + 0x670) : t;
}
