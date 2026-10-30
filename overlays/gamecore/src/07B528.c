/* GAMECORE.XFF @ 0x07B528 (32 B) - getPlayerColCont2
 * Evidence: jal GetSCRCharaAIWorkPtr; return v0+0xDD0
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

char * getPlayerColCont2(void) {
    return GetSCRCharaAIWorkPtr() + 0xDD0;
}
