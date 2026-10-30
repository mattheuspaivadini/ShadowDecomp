/* GAMECORE.XFF @ 0x035130 (28 B) - SCRBirdStartFlap
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x35430
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00035430(void);

void SCRBirdStartFlap(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00035430);
}
