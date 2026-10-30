/* GAMECORE.XFF @ 0x07C648 (28 B) - SCRPlayerSowrdHitSoundLarge
 * Evidence: frame, a1 = address of a .text static (0x07A160), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007A160();

void SCRPlayerSowrdHitSoundLarge(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007A160);
}
