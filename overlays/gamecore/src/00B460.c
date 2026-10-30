/* GAMECORE.XFF @ 0x00B460 (28 B) - nico_deleteMyself
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0xB638
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0000B638(void);

void nico_deleteMyself(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0000B638);
}
