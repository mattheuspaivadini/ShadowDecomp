/* GAMECORE.XFF @ 0x044778 (28 B) - SCRResetCharacterObj4DDynamicsInfo
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x44850
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00044850(void);

void SCRResetCharacterObj4DDynamicsInfo(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00044850);
}
