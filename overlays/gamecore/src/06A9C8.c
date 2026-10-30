/* GAMECORE.XFF @ 0x06A9C8 (28 B) - SCRCanossaWallBreakEnd
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x6AA08
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0006AA08(void);

void SCRCanossaWallBreakEnd(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0006AA08);
}
