/* GAMECORE.XFF @ 0x06BD18 (28 B) - SCRMinoCSetAddFlag
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x6BE98
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0006BE98(void);

void SCRMinoCSetAddFlag(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0006BE98);
}
