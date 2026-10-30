/* GAMECORE.XFF @ 0x06BC00 (28 B) - SCRMinotourCSetFallWeaponFlag
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x6BE60
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0006BE60(void);

void SCRMinotourCSetFallWeaponFlag(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0006BE60);
}
