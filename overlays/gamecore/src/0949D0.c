/* GAMECORE.XFF @ 0x0949D0 (44 B) - SCRConditionPoseidonAngryCountChack
 * Evidence: frame 0x10, `jal GetSCRCharaAIWorkPtr`, `lw [v0+0x41D0]`, then
 * `slt v0, v0, $s0` where $s0 holds the second argument; sibling-free `jr $ra`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionPoseidonAngryCountChack(int unused, int count) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x41D0) < count;
}
