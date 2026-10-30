/* GAMECORE.XFF @ 0x0D29B8 (28 B) - SCRYamori2BeginStand
 * Evidence: frame, a1 = address of a .text static (0x0D3C70), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_000D3C70();

void SCRYamori2BeginStand(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_000D3C70);
}
