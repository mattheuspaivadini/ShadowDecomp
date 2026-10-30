/* GAMECORE.XFF @ 0x0604E0 (20 B) - Init_TimeFloatSpeed
 * Evidence: swc1 f14->+0xC f12->+4 f13->+8,+0
 * UNCONFIRMED: none
 */
void Init_TimeFloatSpeed(float *p, float a, float b, float c) {
    p[1] = a;
    p[0] = b;
    p[2] = b;
    p[3] = c;
}
