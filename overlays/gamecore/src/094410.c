/* GAMECORE.XFF @ 0x094410 (28 B) - SCRPoseidonShoot
 * Evidence: frame, a1 = address of a .text static (0x093968), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_00093968();

void SCRPoseidonShoot(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_00093968);
}
