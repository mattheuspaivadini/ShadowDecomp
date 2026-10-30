/* GAMECORE.XFF @ 0x05CF98 (28 B) - SCRHorseUnLoad
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x5D290
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0005D290(void);

void SCRHorseUnLoad(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0005D290);
}
