/* GAMECORE.XFF @ 0x0428A0 (28 B) - SCRGetYZAngle
 * Evidence: f12=[a0+4], f13=[a0+8], sibling j iosGetATan2fExact
 * UNCONFIRMED: none
 */
float iosGetATan2fExact(float y, float x);

float SCRGetYZAngle(float *v) {
    return iosGetATan2fExact(v[1], v[2]);
}
