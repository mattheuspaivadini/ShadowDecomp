/* GAMECORE.XFF @ 0x064230 (28 B) - SCRLeoTorch2_Disp
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x64478
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00064478(void);

void SCRLeoTorch2_Disp(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00064478);
}
