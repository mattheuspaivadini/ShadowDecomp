/* GAMECORE.XFF @ 0x07C568 (28 B) - SCRPlayerSendDamage
 * Evidence: frame, a1 = address of a .text static (0x07D858), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D858();

void SCRPlayerSendDamage(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D858);
}
