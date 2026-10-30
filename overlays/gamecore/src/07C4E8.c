/* GAMECORE.XFF @ 0x07C4E8 (28 B) - SCRHarpoonLoopStart
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x79A70
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00079A70(void);

void SCRHarpoonLoopStart(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00079A70);
}
