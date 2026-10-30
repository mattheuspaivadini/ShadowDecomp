/* GAMECORE.XFF @ 0x0D29F8 (28 B) - SCRYamoriBReadyToBreeze2
 * Evidence: frame, a1 = address of a .text static (0x0D3C78), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000D3C78();

void SCRYamoriBReadyToBreeze2(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000D3C78);
}
