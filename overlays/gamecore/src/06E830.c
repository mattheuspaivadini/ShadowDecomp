/* GAMECORE.XFF @ 0x06E830 (36 B) - SCRConditionNargaPlayerDamage
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `lw $v0, 0x5AA4($v0)` and
 * `sltu $v0, $zero, $v0` (field != 0) in the return slot.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

int SCRConditionNargaPlayerDamage(void) {
    return *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x5AA4) != 0;
}
