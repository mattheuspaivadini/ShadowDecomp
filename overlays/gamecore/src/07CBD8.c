/* GAMECORE.XFF @ 0x07CBD8 (28 B) - nico_playeGripDamage
 * Evidence: frame, a1 = address of a .text static (0x07DC78), sibling j to RequestCharacterMotionShiftFunc with a0 live.
 * UNCONFIRMED: callback name/signature, a0 type.
 */
void RequestCharacterMotionShiftFunc(int chara, void (*func)());
void func_0007DC78();

void nico_playeGripDamage(int chara) {
    RequestCharacterMotionShiftFunc(chara, func_0007DC78);
}
