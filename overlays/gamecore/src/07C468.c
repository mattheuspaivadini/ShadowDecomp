/* GAMECORE.XFF @ 0x07C468 (28 B) - SCRArrowLoopStart
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x79630
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00079630(void);

void SCRArrowLoopStart(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00079630);
}
