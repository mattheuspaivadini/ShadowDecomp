/* GAMECORE.XFF @ 0x0642B8 (28 B) - SCRLeoFall
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x64628
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00064628(void);

void SCRLeoFall(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00064628);
}
