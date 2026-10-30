/* GAMECORE.XFF @ 0x0CAE10 (28 B) - SCRFallRockSub
 * Evidence: frame, a1 = address of a .text static (0x0CB5D0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000CB5D0();

void SCRFallRockSub(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000CB5D0);
}
