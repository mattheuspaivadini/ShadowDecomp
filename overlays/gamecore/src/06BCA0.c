/* GAMECORE.XFF @ 0x06BCA0 (32 B) - SCRFuncMinoCAtkCountInit
 * Evidence: jal GetSCRCharaAIWorkPtr; sw zero -> [v0+0x41E8]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncMinoCAtkCountInit(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x41E8) = 0;
}
