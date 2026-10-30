/* GAMECORE.XFF @ 0x06A9E8 (28 B) - SCRCanossaWallDelete
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x6AA50
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0006AA50(void);

void SCRCanossaWallDelete(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0006AA50);
}
