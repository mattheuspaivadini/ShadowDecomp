/* GAMECORE.XFF @ 0x07B048 (32 B) - nico_playerGetExpressionChange
 * Evidence: jal GetSCRCharaAIWorkPtr; return v0+0xD10
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

char * nico_playerGetExpressionChange(void) {
    return GetSCRCharaAIWorkPtr() + 0xD10;
}
