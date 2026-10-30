/* GAMECORE.XFF @ 0x07C9F0 (28 B) - SCRWeaponSword
 * Evidence: frame, a1 = address of a .text static (0x07DB68), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007DB68();

void SCRWeaponSword(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007DB68);
}
