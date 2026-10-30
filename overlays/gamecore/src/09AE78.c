/* GAMECORE.XFF @ 0x09AE78 (36 B) - AI_GetAreaDistScale
 * Evidence: `c.lt.s $f12,$f13` + `bc1t`, `mov.s` selects $f12/$f13 into $f0,
 * `div.s $f0,$f0,$f12`, delay-slot `mul.s $f0,$f0,$f0`.
 * UNCONFIRMED: parameter meanings
 
 */
float AI_GetAreaDistScale(float a, float b) {
    float m = a < b ? a : b;
    m = m / a;
    return m * m;
}
