/* GAMECORE.XFF @ 0x055A88 (28 B) - SCRGuardSwordPickupEnd
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x55B10
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00055B10(void);

void SCRGuardSwordPickupEnd(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00055B10);
}
