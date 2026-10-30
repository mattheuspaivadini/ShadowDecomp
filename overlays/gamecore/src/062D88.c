/* GAMECORE.XFF @ 0x062D88 (28 B) - SCRKirinFallRockEnd
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x62FA0
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00062FA0(void);

void SCRKirinFallRockEnd(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00062FA0);
}
