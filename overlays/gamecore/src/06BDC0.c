/* GAMECORE.XFF @ 0x06BDC0 (32 B) - SCRFuncMinoCResetPlayerInCorridorFlag
 * Evidence: jal GetSCRCharaAIWorkPtr; sw zero -> [v0+0x41F4]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncMinoCResetPlayerInCorridorFlag(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x41F4) = 0;
}
