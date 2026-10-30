/* GAMECORE.XFF @ 0x063848 (28 B) - SCRKnightBossPartsBroken
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x63168
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00063168(void);

void SCRKnightBossPartsBroken(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00063168);
}
