/* GAMECORE.XFF @ 0x042BF8 (40 B) - SCRSetCharaMotionPlaySpeedRatioDirect
 * Evidence: the float argument is kept in `$f20` across `jal GetCharacterClass`
 * (saved to the frame at 0x8, `mov.s` in the delay slot) and stored into the
 * class +0x524. `$a0` is forwarded untouched to the getter.
 * UNCONFIRMED: the field meaning (motion play-speed ratio) and the getter's
 * arity.
 
 */
void *GetCharacterClass(void);

void SCRSetCharaMotionPlaySpeedRatioDirect(float ratio) {
    *(float *)((char *)GetCharacterClass() + 0x524) = ratio;
}
