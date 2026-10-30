/* GAMECORE.XFF @ 0x052340 (28 B) - SCRRockReset
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x52388
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00052388(void);

void SCRRockReset(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00052388);
}
