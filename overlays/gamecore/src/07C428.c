/* GAMECORE.XFF @ 0x07C428 (28 B) - SCRArrowStart
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x7D610
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0007D610(void);

void SCRArrowStart(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0007D610);
}
