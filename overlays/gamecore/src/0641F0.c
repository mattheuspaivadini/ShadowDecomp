/* GAMECORE.XFF @ 0x0641F0 (28 B) - SCRLeoTorch0_Disp
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x64338
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00064338(void);

void SCRLeoTorch0_Disp(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00064338);
}
