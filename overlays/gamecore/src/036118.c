/* GAMECORE.XFF @ 0x036118 (28 B) - SCRBossDebugDeath
 * Evidence: frame, a1 = .text address, sibling j RequestCharacterMotionShiftFunc
 * UNCONFIRMED: callback is an unnamed static at .text+0x36158
 */
void RequestCharacterMotionShiftFunc(int chr, void (*fn)(void));
void func_00036158(void);

void SCRBossDebugDeath(int chr) {
    RequestCharacterMotionShiftFunc(chr, func_00036158);
}
