/* GAMECORE.XFF @ 0x01E868 (48 B) - getPlayerMaxGripRatio
 * Evidence: `jal _gameFWorkChk` with `$a0 = 0xC` in the delay slot, then
 * `div.s` by 0x42C80000 (100.0f) of the float result.
 * UNCONFIRMED: the work-field meaning.
 
 */
float _gameFWorkChk(int field);

float getPlayerMaxGripRatio(void) {
    return _gameFWorkChk(0xC) / 100.0f;
}
