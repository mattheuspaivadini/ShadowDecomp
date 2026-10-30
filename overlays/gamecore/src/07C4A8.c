/* GAMECORE.XFF @ 0x07C4A8 (28 B) - SCRHarpoonStart
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x7D670
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0007D670(void);

void SCRHarpoonStart(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0007D670);
}
