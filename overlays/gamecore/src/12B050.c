/* GAMECORE.XFF @ 0x12B050 (24 B) - SCRConditionSoundSignal
 * Evidence: ops ld sd; calls j bgmScriptRecvSoundSignal; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void bgmScriptRecvSoundSignal(int s);
void SCRConditionSoundSignal(int a, int s) {
    bgmScriptRecvSoundSignal(s);
}
