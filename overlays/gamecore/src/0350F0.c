/* GAMECORE.XFF @ 0x0350F0 (28 B) - SCRBirdStartBreath
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x353D0
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_000353D0(void);

void SCRBirdStartBreath(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_000353D0);
}
