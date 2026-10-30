/* GAMECORE.XFF @ 0x0CAAC8 (28 B) - SCRTortoisePulseCharge
 * Evidence: frame, a1 = address of a .text static (0x0CB500), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000CB500();

void SCRTortoisePulseCharge(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000CB500);
}
