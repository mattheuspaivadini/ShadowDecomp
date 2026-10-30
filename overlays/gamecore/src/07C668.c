/* GAMECORE.XFF @ 0x07C668 (28 B) - SCRPlayerSowrdDiveHitSound
 * Evidence: frame, a1 = address of a .text static (0x07A2C0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007A2C0();

void SCRPlayerSowrdDiveHitSound(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007A2C0);
}
