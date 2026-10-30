/* GAMECORE.XFF @ 0x07B028 (32 B) - nico_playerGetExpression
 * Evidence: jal GetSCRCharaAIWorkPtr; return v0+0x5E0
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

char * nico_playerGetExpression(void) {
    return GetSCRCharaAIWorkPtr() + 0x5E0;
}
