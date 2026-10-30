/* GAMECORE.XFF @ 0x07C548 (28 B) - SCRPlayerSendDamageEnd
 * Evidence: frame, a1 = address of a .text static (0x07D838), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D838();

void SCRPlayerSendDamageEnd(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D838);
}
