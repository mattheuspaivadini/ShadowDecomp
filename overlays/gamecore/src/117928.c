/* GAMECORE.XFF @ 0x117928 (24 B) - SCRFuncSetGameFlag
 * Evidence: ops ld sd; calls j _gameFlagSet; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void _gameFlagSet(int f);
void SCRFuncSetGameFlag(int a, int f) {
    _gameFlagSet(f);
}
