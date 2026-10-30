/* GAMECORE.XFF @ 0x07C5E8 (28 B) - SCRPlayerSowrdDeathHitSound
 * Evidence: frame, a1 = address of a .text static (0x079D30), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_00079D30();

void SCRPlayerSowrdDeathHitSound(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_00079D30);
}
