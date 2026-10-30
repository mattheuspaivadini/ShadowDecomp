/* GAMECORE.XFF @ 0x11EDD8 (24 B) - SCRConditionGameFlagCheck
 * Evidence: ops ld sd; calls j _gameFlagChk; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int _gameFlagChk(int f);
int SCRConditionGameFlagCheck(int a, int f) {
    return _gameFlagChk(f);
}
