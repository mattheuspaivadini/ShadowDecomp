/* GAMECORE.XFF @ 0x07C528 (28 B) - SCRPlayerSendDamageStart
 * Evidence: frame, a1 = address of a .text static (0x07D810), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D810();

void SCRPlayerSendDamageStart(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D810);
}
