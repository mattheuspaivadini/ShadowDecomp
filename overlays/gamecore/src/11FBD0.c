/* GAMECORE.XFF @ 0x11FBD0 (24 B) - SCRConditionGetOmakeFlag
 * Evidence: ops ld sd; calls j _omakeGetFlagChk; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int _omakeGetFlagChk(int f);
int SCRConditionGetOmakeFlag(int a, int f) {
    return _omakeGetFlagChk(f);
}
