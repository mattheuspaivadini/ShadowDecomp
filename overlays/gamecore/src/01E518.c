/* GAMECORE.XFF @ 0x01E518 (52 B) - _getPlayerHpRatio
 * Evidence: `$f20` is saved, the result of `.text+0x1E3E0` is kept in `$f20`
 * across the call to `.text+0x1E590`, then `div.s $f0,$f20,$f0`.
 * UNCONFIRMED: the callee prototypes (both targets are unnamed statics).
 
 */
float func_01E3E0(void);
float func_01E590(void);

float _getPlayerHpRatio(void) {
    return func_01E3E0() / func_01E590();
}
