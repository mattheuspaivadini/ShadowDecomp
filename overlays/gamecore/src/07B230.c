/* GAMECORE.XFF @ 0x07B230 (32 B) - getPlayerMVHIST
 * Evidence: jal GetSCRCharaAIWorkPtr; return v0+0xE00
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

char * getPlayerMVHIST(void) {
    return GetSCRCharaAIWorkPtr() + 0xE00;
}
