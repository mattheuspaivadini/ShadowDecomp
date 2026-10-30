/* GAMECORE.XFF @ 0x07C950 (28 B) - SCRPlayerCombatMode
 * Evidence: frame, a1 = address of a .text static (0x07D9A0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D9A0();

void SCRPlayerCombatMode(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D9A0);
}
