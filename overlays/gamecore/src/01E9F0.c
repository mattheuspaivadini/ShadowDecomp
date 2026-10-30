/* GAMECORE.XFF @ 0x01E9F0 (28 B) - SCRPowerReset
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x1EA10
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0001EA10(void);

void SCRPowerReset(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0001EA10);
}
