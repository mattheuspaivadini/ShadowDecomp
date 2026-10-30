/* GAMECORE.XFF @ 0x0416F0 (28 B) - SCRCerberusPollFalldown
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x41928
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00041928(void);

void SCRCerberusPollFalldown(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00041928);
}
