/* GAMECORE.XFF @ 0x07C5A8 (28 B) - SCRPlayerSendDeathDamageLater
 * Evidence: frame, a1 = address of a .text static (0x07D8C8), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D8C8();

void SCRPlayerSendDeathDamageLater(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D8C8);
}
