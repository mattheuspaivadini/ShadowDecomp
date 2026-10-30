/* GAMECORE.XFF @ 0x07C9B0 (28 B) - SCRPlayerPauseEnable
 * Evidence: frame, a1 = address of a .text static (0x07DB48), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007DB48();

void SCRPlayerPauseEnable(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007DB48);
}
