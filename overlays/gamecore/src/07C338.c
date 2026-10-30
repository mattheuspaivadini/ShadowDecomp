/* GAMECORE.XFF @ 0x07C338 (28 B) - SCRWeaponReload
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x78C20
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00078C20(void);

void SCRWeaponReload(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00078C20);
}
