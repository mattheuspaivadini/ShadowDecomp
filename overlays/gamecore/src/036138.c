/* GAMECORE.XFF @ 0x036138 (28 B) - SCRMammothBreaksWall
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x36198
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00036198(void);

void SCRMammothBreaksWall(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00036198);
}
