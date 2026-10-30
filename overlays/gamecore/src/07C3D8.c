/* GAMECORE.XFF @ 0x07C3D8 (28 B) - SCRItemTakeDelete
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x7D5F8
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0007D5F8(void);

void SCRItemTakeDelete(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0007D5F8);
}
