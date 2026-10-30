/* GAMECORE.XFF @ 0x035110 (28 B) - SCRBirdStopBreath
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x35400
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00035400(void);

void SCRBirdStopBreath(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00035400);
}
