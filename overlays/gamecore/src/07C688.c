/* GAMECORE.XFF @ 0x07C688 (28 B) - SCRPlayerFullPower
 * Evidence: frame, a1 = address of a .text static (0x07D960), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007D960();

void SCRPlayerFullPower(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007D960);
}
