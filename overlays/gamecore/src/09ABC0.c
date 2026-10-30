/* GAMECORE.XFF @ 0x09ABC0 (56 B) - AI_GetInterRatio
 * Evidence: `sub.s f14,f14,f13`, `c.eq.s` against `mtc1 $zero`, `bc1t` to
 * `jr` with `$f0 = $f15` preloaded in the delay slot; otherwise
 * `(f12-f13)*(f16-f15)/f14 + f15`.
 * UNCONFIRMED: parameter meanings
 
 */
float AI_GetInterRatio(float a0, float a1, float a2, float a3, float a4) {
    float d = a2 - a1;
    if (d == 0.0f) {
        return a3;
    }
    return (a0 - a1) * (a4 - a3) / d + a3;
}
