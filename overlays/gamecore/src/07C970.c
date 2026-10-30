/* GAMECORE.XFF @ 0x07C970 (28 B) - SCRPlayerNonCombatMode
 * Evidence: frame, a1 = address of a .text static (0x07D9E8), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D9E8();

void SCRPlayerNonCombatMode(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D9E8);
}
