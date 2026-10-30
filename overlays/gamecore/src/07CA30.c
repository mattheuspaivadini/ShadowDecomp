/* GAMECORE.XFF @ 0x07CA30 (28 B) - SCRHorseKick
 * Evidence: frame, a1 = address of a .text static (0x07DC08), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007DC08();

void SCRHorseKick(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007DC08);
}
