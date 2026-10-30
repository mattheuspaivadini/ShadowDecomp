/* GAMECORE.XFF @ 0x0566E8 (28 B) - SCRGuardArrowShoot
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x56828
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00056828(void);

void SCRGuardArrowShoot(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00056828);
}
