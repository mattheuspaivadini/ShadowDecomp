/* GAMECORE.XFF @ 0x064318 (28 B) - SCRLeoDashAttack
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x64640
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00064640(void);

void SCRLeoDashAttack(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00064640);
}
