/* GAMECORE.XFF @ 0x06BD58 (32 B) - SCRConditionMinoCAddFlagChack
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x41EC]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionMinoCAddFlagChack(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x41EC);
}
