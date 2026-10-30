/* GAMECORE.XFF @ 0x062F30 (32 B) - SCRFuncKirinFallRockTimerSetFlagOff
 * Evidence: jal GetSCRCharaAIWorkPtr; sw zero -> [v0+0x41B8]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncKirinFallRockTimerSetFlagOff(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x41B8) = 0;
}
