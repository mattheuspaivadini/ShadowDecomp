/* GAMECORE.XFF @ 0x09A288 (52 B) - AI_GetAccelB_at0
 * Evidence: `lui/ori 0x3D08AB85` (= 0.0333667f; EE-GCC 2.96 truncates the
 * decimal literal `0.0333667f` to exactly that bit pattern), `sub.s
 * $f13,$f13,$f12`, `c.lt.s $f14,$f0` + `bc1t` keeping the constant in $f0,
 * `add.s $f13,$f13,$f13`, `div.s $f0,$f13,$f0`.
 * The ternary is declared BEFORE the difference: that is what makes 2.96 tie
 * the difference to $f13 (arg1) instead of $f12.
 * UNCONFIRMED: parameter meanings
 
 */
float AI_GetAccelB_at0(float from, float to, float time) {
    float m = time < 0.0333667f ? 0.0333667f : time;
    float d = to - from;
    return (d + d) / m;
}
