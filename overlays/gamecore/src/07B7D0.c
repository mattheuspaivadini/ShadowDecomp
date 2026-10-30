/* GAMECORE.XFF @ 0x07B7D0 (32 B) - getTorchObj
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x150]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int getTorchObj(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x150);
}
