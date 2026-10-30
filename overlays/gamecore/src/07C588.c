/* GAMECORE.XFF @ 0x07C588 (28 B) - SCRPlayerSendDamageLater
 * Evidence: frame, a1 = address of a .text static (0x079BA0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_00079BA0();

void SCRPlayerSendDamageLater(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_00079BA0);
}
