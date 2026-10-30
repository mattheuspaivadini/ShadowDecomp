/* GAMECORE.XFF @ 0x07C448 (28 B) - SCRArrowContinue
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x794A8
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_000794A8(void);

void SCRArrowContinue(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_000794A8);
}
