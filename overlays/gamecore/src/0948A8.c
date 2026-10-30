/* GAMECORE.XFF @ 0x0948A8 (36 B) - SCRConditionPoseidonMissAttackCheck
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `lw $v0, 0x41C4($v0)` and
 * `slti $v0, $v0, 1` (counter < 1) in the return slot.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

int SCRConditionPoseidonMissAttackCheck(void) {
    return *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41C4) < 1;
}
