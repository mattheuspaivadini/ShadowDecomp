/* GAMECORE.XFF @ 0x07C608 (28 B) - SCRPlayerSowrdHitSound
 * Evidence: frame, a1 = address of a .text static (0x079EA0), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_00079EA0();

void SCRPlayerSowrdHitSound(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_00079EA0);
}
