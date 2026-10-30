/* GAMECORE.XFF @ 0x07C508 (28 B) - SCRHarpoonLoopEnd
 * Evidence: frame, a1 = address of a .text static (0x07D6D0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D6D0();

void SCRHarpoonLoopEnd(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D6D0);
}
