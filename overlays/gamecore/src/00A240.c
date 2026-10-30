/* GAMECORE.XFF @ 0x00A240 (12 B) - GAMEUTIL_set_parameter_col_plane_info_filter
 * Evidence: swc1 f12 -> +0x70, f13 -> +0x74
 * UNCONFIRMED: none
 */
void GAMEUTIL_set_parameter_col_plane_info_filter(float *p, float a, float b) {
    p[28] = a;
    p[29] = b;
}
