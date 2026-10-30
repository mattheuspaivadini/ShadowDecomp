/* GAMECORE.XFF @ 0x063920 (36 B) - SCRConditionKnightGetStandKeyFlag
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw $v0, 0x41B0($v0)` then
 * `andi $v0, $v0, 1`: the low bit of a flag word.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

int SCRConditionKnightGetStandKeyFlag(void) {
    return *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41B0) & 1;
}
