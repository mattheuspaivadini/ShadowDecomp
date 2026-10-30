/* GAMECORE.XFF @ 0x09AEA0 (36 B) - AI_GetAreaDistScale2
 * Evidence: same select as AI_GetAreaDistScale but `jr` delay slot is `nop`
 * (no final square).
 * UNCONFIRMED: parameter meanings
 
 */
float AI_GetAreaDistScale2(float a, float b) {
    float m = a < b ? a : b;
    return m / a;
}
