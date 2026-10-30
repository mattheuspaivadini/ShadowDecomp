/* GAMECORE.XFF @ 0x07C628 (28 B) - SCRPlayerSowrdHitSoundMiddle
 * Evidence: frame, a1 = address of a .text static (0x07A000), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007A000();

void SCRPlayerSowrdHitSoundMiddle(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007A000);
}
