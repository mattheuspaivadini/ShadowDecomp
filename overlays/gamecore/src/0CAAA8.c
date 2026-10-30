/* GAMECORE.XFF @ 0x0CAAA8 (28 B) - SCRTortoiseShoot
 * Evidence: frame, a1 = address of a .text static (0x0CB4C8), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000CB4C8();

void SCRTortoiseShoot(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000CB4C8);
}
