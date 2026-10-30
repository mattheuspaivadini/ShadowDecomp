/* GAMECORE.XFF @ 0x01E5A8 (52 B) - setPlayerMaxHp
 * Evidence: `c.lt.s` against 0x440E8000 (570.0f) with `bc1t` skipping a
 * `mov.s $f0,$f12`, then `mov.s $f12,$f0` and `_gameFWorkSet(0xB, value)`; the
 * double `mov.s` is the ternary result materialised in `$f0` and copied to the
 * argument register.
 * UNCONFIRMED: the work-field meaning.
 
 */
void _gameFWorkSet(int field, float value);

void setPlayerMaxHp(float hp) {
    _gameFWorkSet(0xB, hp > 570.0f ? 570.0f : hp);
}
