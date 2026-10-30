/* GAMECORE.XFF @ 0x0123F0 (40 B) - nico_GetCharacterAttackedFlag
 * Evidence: `jal GetDamageClass`, `lw $v0, 0($v0)`, then `xori 3` +
 * `sltiu 1`: the word equals 3.
 * UNCONFIRMED: the state value meaning and the callee prototype.
 
 */
void *GetDamageClass(void);

int nico_GetCharacterAttackedFlag(void) {
    return *(int *)GetDamageClass() == 3;
}
