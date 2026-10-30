/* GAMECORE.XFF @ 0x03F710 (28 B) - SCRBuddhaShoot
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x3FA98
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_0003FA98(void);

void SCRBuddhaShoot(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_0003FA98);
}
