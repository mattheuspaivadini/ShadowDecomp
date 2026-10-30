/* GAMECORE.XFF @ 0x0642F8 (28 B) - SCRLeoDashAttackEnd
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x64638
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00064638(void);

void SCRLeoDashAttackEnd(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00064638);
}
