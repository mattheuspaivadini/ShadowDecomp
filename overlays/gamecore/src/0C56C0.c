/* GAMECORE.XFF @ 0x0C56C0 (28 B) - SCRDirectionalArrowEnd
 * Evidence: frame, a1 = address of a .text static (0x0C56E0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000C56E0();

void SCRDirectionalArrowEnd(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000C56E0);
}
