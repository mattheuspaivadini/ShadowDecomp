/* GAMECORE.XFF @ 0x064210 (28 B) - SCRLeoTorch1_Disp
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x643D8
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_000643D8(void);

void SCRLeoTorch1_Disp(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_000643D8);
}
