/* GAMECORE.XFF @ 0x07C378 (28 B) - SCRFoodTakeEnd
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x78D68
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00078D68(void);

void SCRFoodTakeEnd(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00078D68);
}
