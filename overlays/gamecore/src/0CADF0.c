/* GAMECORE.XFF @ 0x0CADF0 (28 B) - SCRFallRockDelete
 * Evidence: frame, a1 = address of a .text static (0x0CB580), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000CB580();

void SCRFallRockDelete(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000CB580);
}
