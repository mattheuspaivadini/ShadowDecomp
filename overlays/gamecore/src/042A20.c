/* GAMECORE.XFF @ 0x042A20 (44 B) - SCRCharaDead
 * Evidence: `jal GetCharacterClass`, `ld $v1, 0x858($v0)`, `ori 0x200`, then
 * `sd $v1, 0x858($v0)`: a 64-bit flag word.
 * UNCONFIRMED: the flag bit meaning and the getter's arity.
 
 */
void *GetCharacterClass(void);

void SCRCharaDead(void) {
    *(long *)((char *)GetCharacterClass() + 0x858) |= 0x200;
}
