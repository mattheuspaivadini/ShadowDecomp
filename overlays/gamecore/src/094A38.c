/* GAMECORE.XFF @ 0x094A38 (36 B) - SCRConditionPoseidonDamageFlagSet
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw 1 -> [v0+0x41BC]`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRConditionPoseidonDamageFlagSet(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x41BC) = 1;
}
