/* GAMECORE.XFF @ 0x07B508 (32 B) - getPlayerColCont
 * Evidence: jal GetSCRCharaAIWorkPtr; return v0+0xDC0
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

char * getPlayerColCont(void) {
    return GetSCRCharaAIWorkPtr() + 0xDC0;
}
