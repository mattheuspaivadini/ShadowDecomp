/* GAMECORE.XFF @ 0x052320 (28 B) - SCRRockFall
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x52360
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00052360(void);

void SCRRockFall(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00052360);
}
