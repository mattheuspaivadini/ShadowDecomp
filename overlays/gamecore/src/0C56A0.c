/* GAMECORE.XFF @ 0x0C56A0 (28 B) - SCRDirectionalArrowBegin
 * Evidence: frame, a1 = address of a .text static (0x0C3B68), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000C3B68();

void SCRDirectionalArrowBegin(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000C3B68);
}
