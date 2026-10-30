/* GAMECORE.XFF @ 0x00D500 (12 B) - set_base_vel_nico_yaw_pitch_cntrl
 * Evidence: swc1 f12 -> +0x54, f13 -> +0x60
 * UNCONFIRMED: none
 */
void set_base_vel_nico_yaw_pitch_cntrl(float *p, float a, float b) {
    p[21] = a;
    p[24] = b;
}
