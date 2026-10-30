/* GAMECORE.XFF @ 0x064250 (28 B) - SCRLeoTorch3_Disp
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x64518
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00064518(void);

void SCRLeoTorch3_Disp(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00064518);
}
