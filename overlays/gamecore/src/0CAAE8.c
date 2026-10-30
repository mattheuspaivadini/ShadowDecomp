/* GAMECORE.XFF @ 0x0CAAE8 (28 B) - SCRTortoisePulseChargeStop
 * Evidence: frame, a1 = address of a .text static (0x0CB560), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000CB560();

void SCRTortoisePulseChargeStop(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000CB560);
}
