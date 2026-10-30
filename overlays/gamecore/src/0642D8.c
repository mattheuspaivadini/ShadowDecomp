/* GAMECORE.XFF @ 0x0642D8 (28 B) - SCRLeoDamage
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x64630
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00064630(void);

void SCRLeoDamage(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00064630);
}
