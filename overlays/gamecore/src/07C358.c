/* GAMECORE.XFF @ 0x07C358 (28 B) - SCRFoodTakeBegin
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x7D550
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0007D550(void);

void SCRFoodTakeBegin(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0007D550);
}
