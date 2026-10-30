/* GAMECORE.XFF @ 0x064298 (28 B) - SCRLeoArmorBroken
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x645B8
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_000645B8(void);

void SCRLeoArmorBroken(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_000645B8);
}
