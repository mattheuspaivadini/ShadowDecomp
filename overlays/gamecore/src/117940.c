/* GAMECORE.XFF @ 0x117940 (24 B) - SCRFuncClsGameFlag
 * Evidence: ops ld sd; calls j _gameFlagCls; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void _gameFlagCls(int f);
void SCRFuncClsGameFlag(int a, int f) {
    _gameFlagCls(f);
}
