/* GAMECORE.XFF @ 0x00CF88 (20 B) - set_yaw_pitch_input_border_parameter_nico_yaw_pitch_cntrl
 * Evidence: swc1 f12..f15 -> +0x6C,+0x70,+0x74,+0x78
 * UNCONFIRMED: none
 */
void set_yaw_pitch_input_border_parameter_nico_yaw_pitch_cntrl(float *p, float a, float b, float c, float d) {
    p[27] = a;
    p[28] = b;
    p[29] = c;
    p[30] = d;
}
