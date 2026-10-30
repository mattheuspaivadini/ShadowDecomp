/* GAMECORE.XFF @ 0x042930 (40 B) - SCRCharaTurnDirectInput
 * Evidence: the float argument is kept in `$f20` across `jal GetCharacterClass`
 * (saved to the frame at 0x8, `mov.s` in the delay slot) and stored into the
 * class +0x7E8. `$a0` is forwarded untouched to the getter.
 * UNCONFIRMED: the field meaning (a direct turn input) and the getter's arity.
 
 */
void *GetCharacterClass(void);

void SCRCharaTurnDirectInput(float angle) {
    *(float *)((char *)GetCharacterClass() + 0x7E8) = angle;
}
