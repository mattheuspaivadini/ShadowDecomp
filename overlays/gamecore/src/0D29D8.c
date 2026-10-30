/* GAMECORE.XFF @ 0x0D29D8 (28 B) - SCRYamoriBReadyToBreeze
 * Evidence: frame, a1 = address of a .text static (0x0D15C0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000D15C0();

void SCRYamoriBReadyToBreeze(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000D15C0);
}
