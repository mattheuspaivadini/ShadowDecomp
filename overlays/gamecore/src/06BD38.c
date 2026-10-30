/* GAMECORE.XFF @ 0x06BD38 (28 B) - SCRMinoCResetAddFlag
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x6BED0
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0006BED0(void);

void SCRMinoCResetAddFlag(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0006BED0);
}
