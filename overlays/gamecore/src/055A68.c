/* GAMECORE.XFF @ 0x055A68 (28 B) - SCRGuardSwordPickup
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x55AA8
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00055AA8(void);

void SCRGuardSwordPickup(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00055AA8);
}
