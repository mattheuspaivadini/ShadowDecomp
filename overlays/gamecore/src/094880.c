/* GAMECORE.XFF @ 0x094880 (40 B) - SCRFuncPoseidonMissAttackAdd
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw 0x41C4`, `addiu -1`, `sw 0x41C4`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncPoseidonMissAttackAdd(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41C4) -= 1;
}
