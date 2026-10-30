/* GAMECORE.XFF @ 0x07C398 (28 B) - SCRItemTakeBegin
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x7D578
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0007D578(void);

void SCRItemTakeBegin(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0007D578);
}
