/* GAMECORE.XFF @ 0x0F25C0 (20 B) - get_mode_common_data_filter_base_dist_to_look_at
 * Evidence: frame 0x40 allocated, load pointer at a0 then float at +0x150
 * UNCONFIRMED: unused 0x40 B local reproduces the frame (inlined helper?)
 */
float get_mode_common_data_filter_base_dist_to_look_at(char *p) {
    char buf[0x40];
    return *(float *)(*(char **)p + 0x150);
}
