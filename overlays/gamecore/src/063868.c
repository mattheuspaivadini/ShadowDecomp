/* GAMECORE.XFF @ 0x063868 (28 B) - SCRKnightBossPartsDelete
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x63948
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00063948(void);

void SCRKnightBossPartsDelete(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00063948);
}
