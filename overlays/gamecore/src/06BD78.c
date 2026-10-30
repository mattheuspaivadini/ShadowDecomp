/* GAMECORE.XFF @ 0x06BD78 (32 B) - SCRConditionMinoCWallCaseFlagChack
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x41F0]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionMinoCWallCaseFlagChack(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x41F0);
}
