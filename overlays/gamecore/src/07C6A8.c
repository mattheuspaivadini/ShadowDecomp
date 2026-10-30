/* GAMECORE.XFF @ 0x07C6A8 (28 B) - SCRPlayerFullPowerAndHp
 * Evidence: frame, a1 = address of a .text static (0x07D978), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D978();

void SCRPlayerFullPowerAndHp(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D978);
}
