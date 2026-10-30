/* GAMECORE.XFF @ 0x07C990 (28 B) - SCRPlayerPauseDisable
 * Evidence: frame, a1 = address of a .text static (0x07DB28), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007DB28();

void SCRPlayerPauseDisable(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007DB28);
}
