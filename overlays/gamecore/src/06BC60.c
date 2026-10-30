/* GAMECORE.XFF @ 0x06BC60 (32 B) - SCRConditionMinoCTargetWallChangeChack
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x41F8]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionMinoCTargetWallChangeChack(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x41F8);
}
