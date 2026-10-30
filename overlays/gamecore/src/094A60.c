/* GAMECORE.XFF @ 0x094A60 (36 B) - SCRConditionPoseidonDamageFlagReset
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw $zero -> [v0+0x41D8]` and
 * `sw $zero -> [v0+0x41BC]` (image order).
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRConditionPoseidonDamageFlagReset(void) {
    char *p = GetSCRCharaAIWorkPtr();
    *(int *)(p + 0x41BC) = 0;
    *(float *)(p + 0x41D8) = 0.0f;
}
