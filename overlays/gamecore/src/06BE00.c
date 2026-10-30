/* GAMECORE.XFF @ 0x06BE00 (28 B) - SCRMinotourCResetWeaponCameraFlag
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x6BF08
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0006BF08(void);

void SCRMinotourCResetWeaponCameraFlag(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0006BF08);
}
