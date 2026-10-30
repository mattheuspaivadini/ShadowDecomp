/* GAMECORE.XFF @ 0x09A760 (36 B) - AI_GetVelocity2
 * Evidence: `lui at,0x3F00` (0.5f), `mul.s f13,f13,f15`, `mul.s f12,f12,f0`,
 * two more `mul.s f12,f12,f15`, `add.s f0,f14,f12`, tail `add.s f0,f0,f13`.
 * UNCONFIRMED: parameter meanings
 
 */
float AI_GetVelocity2(float a0, float a1, float a2, float a3) {
    float v = a1 * a3;
    float p = a0 * 0.5f;
    p = p * a3;
    p = p * a3;
    return a2 + p + v;
}
