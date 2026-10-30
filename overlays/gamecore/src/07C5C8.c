/* GAMECORE.XFF @ 0x07C5C8 (28 B) - SCRPlayerSendDiveDamageLater
 * Evidence: frame, a1 = address of a .text static (0x079C68), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_00079C68();

void SCRPlayerSendDiveDamageLater(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_00079C68);
}
