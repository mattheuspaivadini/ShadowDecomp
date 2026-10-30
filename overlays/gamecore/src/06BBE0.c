/* GAMECORE.XFF @ 0x06BBE0 (28 B) - SCRMinotourCFallWeapon
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x6BE20
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0006BE20(void);

void SCRMinotourCFallWeapon(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0006BE20);
}
