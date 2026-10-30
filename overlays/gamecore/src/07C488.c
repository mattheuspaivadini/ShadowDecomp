/* GAMECORE.XFF @ 0x07C488 (28 B) - SCRArrowLoopEnd
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x797C8
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_000797C8(void);

void SCRArrowLoopEnd(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_000797C8);
}
