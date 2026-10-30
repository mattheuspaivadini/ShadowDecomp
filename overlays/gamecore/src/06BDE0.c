/* GAMECORE.XFF @ 0x06BDE0 (32 B) - SCRFuncMinoCPlayerInCorridorFlagChack
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x41F4]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRFuncMinoCPlayerInCorridorFlagChack(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x41F4);
}
