/* GAMECORE.XFF @ 0x06BC80 (32 B) - SCRFuncMinoCTargetWallReset
 * Evidence: jal GetSCRCharaAIWorkPtr; sw zero -> [v0+0x41F8]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncMinoCTargetWallReset(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x41F8) = 0;
}
