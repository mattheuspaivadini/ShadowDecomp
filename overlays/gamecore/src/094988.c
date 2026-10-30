/* GAMECORE.XFF @ 0x094988 (40 B) - SCRFuncPoseidonAngryCountAdd
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw 0x41D0`, `addiu 1`, `sw 0x41D0`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncPoseidonAngryCountAdd(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41D0) += 1;
}
