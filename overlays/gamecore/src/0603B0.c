/* GAMECORE.XFF @ 0x0603B0 (24 B) - Init_TimeFloatInter
 * Evidence: swc1 f15->+0x10 f14->+0 f12->+8 f13->+0xC,+4
 * UNCONFIRMED: none
 */
void Init_TimeFloatInter(float *p, float a, float b, float c, float d) {
    p[0] = c;
    p[2] = a;
    p[1] = b;
    p[3] = b;
    p[4] = d;
}
