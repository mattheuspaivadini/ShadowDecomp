/* GAMECORE.XFF @ 0x07C4C8 (28 B) - SCRHarpoonContinue
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x79940
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00079940(void);

void SCRHarpoonContinue(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00079940);
}
