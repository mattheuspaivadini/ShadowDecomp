/* GAMECORE.XFF @ 0x07C3B8 (28 B) - SCRItemTakeEnd
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x7D5B0
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0007D5B0(void);

void SCRItemTakeEnd(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0007D5B0);
}
