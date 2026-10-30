/* GAMECORE.XFF @ 0x07C9D0 (28 B) - SCRPlayerTorchThrow
 * Evidence: frame, a1 = address of a .text static (0x07AA10), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007AA10();

void SCRPlayerTorchThrow(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007AA10);
}
