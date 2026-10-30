/* GAMECORE.XFF @ 0x042880 (28 B) - SCRGetXZAngle
 * Evidence: f12=[a0], f13=[a0+8], sibling j iosGetATan2fExact
 * UNCONFIRMED: none
 */
float iosGetATan2fExact(float y, float x);

float SCRGetXZAngle(float *v) {
    return iosGetATan2fExact(v[0], v[2]);
}
