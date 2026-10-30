/* GAMECORE.XFF @ 0x11FBE8 (32 B) - SCRConditionChkDisplayOmakeCompleteAlert
 * Evidence: ops lw; data dispCompleteAlertHard+0x0, dispCompleteAlertNormal+0x0
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int dispCompleteAlertNormal;
extern int dispCompleteAlertHard;
int SCRConditionChkDisplayOmakeCompleteAlert(int a, int hard) {
    return hard ? dispCompleteAlertHard : dispCompleteAlertNormal;
}
